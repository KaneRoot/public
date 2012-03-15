/*
 * Process Control Blocks
 */

#ifndef __SIMUL_H
#define __SIMUL_H

/******************************************************************************
 * Definition des structures de donnees
 */

/* Bloc de controle d'un processus (PCB = process control block) */
struct pcb
{
    int pid ;				/* ident du processus */
    int start_time ;			/* "date" de debut */
    int duration ;			/* duree estimee du processus */
    int prio ;				/* pour la gestion des priorites */
    int cpu_time ;			/* temps cpu */
} ;

#define	MAX_PRIO	32

/******************************************************************************
 * Operations sur les PCB
 */

/* Creation d'un nouveau processus */
struct pcb *pcb_create (int pid, int date, int duration, int prio) ;

/* Suppression d'un nouveau processus */
void pcb_destroy (struct pcb *pcb) ;

/******************************************************************************
 * Operations generiques de l'ordonnanceur
 *
 * La structure de donnees est opaque (elle n'est connue que dans le
 * fichier source de l'ordonnanceur, car elle n'est pas necessaire
 * ailleurs).
 */

/* Initialisation de la structure de donnees */
void queue_init (void) ;

/* Suppression du premier processus de la file */
void queue_remove_first (struct pcb *p) ;

/* Suppression d'un processus quelconque de la file */
void queue_remove_any (struct pcb *p) ;

/* Insertion du processus en fin de file */
void queue_insert (struct pcb *p) ;

/* Affichage de la file */
void queue_display (void) ;

/* Ordonnanceur */
struct pcb *schedule (struct pcb *curproc) ;

#endif
