#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "simul.h"

/*
 * Valeurs par defaut du simulateur
 */

#define	PROB_CREATE		0.7
#define	DURATION_CREATE		100
#define	DURATION_TOTAL		1000
#define	QUANTUM			5
#define	MAX_DURATION		10

/*
 * Gestion des statistiques
 */

struct stats
{
    int nproc ;			/* nombre de processus crees au total */
    int maxdur ;		/* duree maximum d'un processus */
    int maxload ;		/* charge maximum */
    int sum_cpu ;		/* duree totale d'execution des processus */
    int sum_elapsed ;		/* duree totale de traitement des processus */
    int nsched ;		/* nombre d'appels a l'ordonnanceur */
} ;

/*
 * Prototypes des fonctions definies dans ce fichier
 */

void usage (char *prog) ;
void update_stats (struct stats *s, int date, int nproc, struct pcb *p) ;
void display_stats (int date, struct stats *s) ;
void init_myrandom (void) ;
double myrandom (void) ;
void simulate (int trace, double prob_create, int duration_create, int duration_total, int quantum, int max_duration) ;

/*
 * Fonction principale du simulateur
 */

int main (int argc, char *argv [])
{
    extern char *optarg ;
    extern int optind ;
    int opt ;

    int trace = 0 ;
    double prob_create = PROB_CREATE ;
    int duration_create = DURATION_CREATE ;
    int duration_total = DURATION_TOTAL ;
    int quantum = QUANTUM ;
    int max_duration = MAX_DURATION ;
    int init_random = 0 ;

    while ((opt = getopt (argc, argv, "tip:c:s:q:m:")) != EOF)
    {
		switch (opt)
		{
			case 't' :			/* tracer les creations de processus */
			trace++ ;
			break ;
			case 'i' :			/* initialise le generateur d'alea */
			init_random = 1 ;
			break ;
			case 'p' :			/* probabilite de creation de processus */
			prob_create = atof (optarg) ;
			break ;
			case 'c' :			/* duree autorisee pour la creation de processus */
			duration_create = atoi (optarg) ;
			break ;
			case 's' :			/* duree totale de la simulation */
			duration_total = atoi (optarg) ;
			break ;
			case 'q' :			/* duree du quantum */
			quantum = atoi (optarg) ;
			break ;
			case 'm' :			/* duree maximum d'un processus */
			max_duration = atoi (optarg) ;
			break ;
			case '?' :
			default :
			usage (argv [0]) ;
		}
    }

    if (init_random)
	init_myrandom () ;

    simulate (trace, prob_create, duration_create, duration_total, quantum, max_duration) ;
    exit (0) ;
}

/*
 * Utile pour rappeler la syntaxe
 */

void usage (char *prog)
{
    char *p ;

    fprintf (stderr, "usage: %s [-t][-i][-p prob][-c duration][-s duration][-q quantum][-m maxdur]\n", prog) ;
    exit (1) ;
}

/*
 * Met à jour les statistiques d'un processus, procédure destinée à
 * être utilisé lors de la terminaison du processus
 */

void update_stats (struct stats *s, int date, int nproc, struct pcb *p)
{
    s->nproc++ ;
    if (p->cpu_time > s->maxdur)
		s->maxdur = p->cpu_time ;
    if (nproc > s->maxload)
		s->maxload = nproc ;
    s->sum_cpu += p->cpu_time ;
    s->sum_elapsed += date - p->start_time ;
}

/*
 * Affichage des statistiques
 */

void display_stats (int date, struct stats *s)
{
    printf ("Simulation time = %d\n", date) ;
    printf ("Process count = %d, schedule count = %d\n", s->nproc, s->nsched) ;
    printf ("Max process duration = %d, max load = %d\n", s->maxdur, s->maxload) ;
    printf ("Process mean CPU time = %f, mean elapsed time = %f\n",
	    (double) s->sum_cpu / s->nproc, (double) s->sum_elapsed / s->nproc) ;
}

/*
 * Initialise le generateur de nombre pseudo-aleatoire. Ne pas l'initialiser
 * est utile pour avoir des resultats identiques d'une execution a l'autre,
 * ce qui sert pour le debug.
 */

void init_myrandom (void)
{
    time_t t ;

    t = time (NULL) ;
    srandom (t) ;
}

/*
 * Renvoie un resultat pseudo-aleatoire dans [0..1[
 */

double myrandom (void)
{
    double d ;

    /*
     * random() est preferee a rand() car meilleur alea
     * random() renvoie un resultat entier compris entre 0 et 2^31-1
     *
     * Attention aux conversions de type explicites et implicites :
     * - le resultat de random() est converti en double
     * - 1 est converti en unsigned int, sinon le decalage risque
     *	 de donner un nombre negatif
     * - 1<<31 est ensuite converti implicitement de unsigned int
     *   vers double pour faire la division.
     * Le resultat est donc dans [0..1[
     */
    d = (double) random () / ((unsigned int) 1<<31) ; /* valeur entre 0 et 1 */
    return d ;
}

/*
 * Simule la creation et l'ordonnancement de processus, et rapporte
 * des statistiques a la fin de l'execution.
 * Necessite un ordonnanceur sous la forme d'une fonction sched()
 */

void simulate (int trace, double prob_create, int duration_create, int duration_total, int quantum, int max_duration)
{
    struct pcb *curproc ;	/* processus elu, ou NULL */
    int pid ;			/* dernier pid affecte */
    int date, last_sched ;	/* date courante, et de dernier ordonnancement */
    int nproc ;			/* nombre de processus actifs a cet instant */
    struct stats stats ;	/* stats regroupees pour la lisibilite */

    queue_init () ;

    last_sched = date = 0 ;
    pid = 0 ;
    nproc = 0 ;
    memset (&stats, 0, sizeof stats) ;
    curproc = NULL ;

    /*
     * La simulation dure maximum duration_total unites, a moins qu'il n'y ait
     * plus aucun processus
     */

    while (date < duration_total || (date > duration_create && nproc > 0))
    {
	/*
	 * A chaque tour de cette boucle, c'est comme si l'horloge
	 * avait interrompu le processeur : le systeme reprend la
	 * main alors qu'un processus tourne (s'il y a un processus
	 * sur le processeur).
	 */

	if (trace >= 2)
	    printf ("%d curproc=<%d>\n", date, (curproc == NULL) ? -1 : curproc->pid) ;

	if (curproc != NULL)
	{
	    /*
	     * mettre a jour les informations du processus actuellement
	     * sur le processeur
	     */
	    curproc->cpu_time++ ;
	    if (curproc->cpu_time >= curproc->duration)
	    {
		update_stats (&stats, date, nproc, curproc) ;
		if (trace >= 1)
		    printf ("%d - pid=%-3d cpu_time=%-3d elapsed=%-3d\n",
				    date, curproc->pid, curproc->cpu_time,
				    date - curproc->start_time) ;

		queue_remove_any (curproc) ;
		pcb_destroy (curproc) ;
		curproc = NULL ;	/* il n'y a plus de processus courant */
		nproc-- ;
	    }
	}

	/*
	 * Pendant la premiere periode : creation de nouveaux processus
	 * selon une certaine probabilite.
	 */

	if (date < duration_create && myrandom () < prob_create)
	{
	    int duration, prio ;
	    struct pcb *p ;

	    pid++ ;
	    duration = myrandom () * (max_duration-1) + 1 ;
	    prio = myrandom () * MAX_PRIO ;
	    if (trace >= 1)
		printf ("%d + pid=%-3d duration=%-3d prio=%-2d\n",
				date, pid, duration, prio) ;
	    p = pcb_create (pid, date, duration, prio) ;
	    queue_insert (p) ;
	    nproc++ ;
	}

	/*
	 * Pendant toute la duree de la simulation, on provoque
	 * un ordonnancement si necessaire (nouveau processus et
	 * file vide, ou terminaison du processus courant), ou bien
	 * a chaque quantum
	 */

	if (curproc == NULL || date - last_sched >= quantum)
	{
	    curproc = schedule (curproc) ;
	    stats.nsched++ ;
	    last_sched = date ;
	}

	date++ ;
    }

    /*
     * Rapport de fin de simulation
     */

    display_stats (date, &stats) ;
}
