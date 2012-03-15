#include <stdio.h>
#include <stdlib.h>

#include "simul.h"

/******************************************************************************
 * Structures de donnees
 *
 * Cette structure de donnees est opaque : elle n'est pas connue
 * a l'exterieur de ce fichier source.
 */

/* Cellule d'une file de processus */
struct cell
{
    struct pcb *proc ;
    struct cell *next ;
} ;

/* La file de processus pour l'ordonnanceur round-robin */
struct cell *rrqueue ;

/******************************************************************************
 * Operations generiques de l'ordonnanceur
 */

/*
 * Initialisation de la structure de donnees
 */

void queue_init (void)
{
    rrqueue = NULL ;
}

/*
 * Premier processus de la file
 */

struct pcb *queue_head (void)
{
    struct pcb *p ;

    if (rrqueue != NULL)
		p = rrqueue->next->proc ;
    else p = NULL ;

    return p ;
}

/*
 * Suppression du premier processus de la file
 * On suppose que le pcb existe forcement
 */

void queue_remove_first (struct pcb *p)
{
    if (rrqueue != NULL)
    {
		struct cell *c ;

		c = rrqueue->next ;
		if (rrqueue->next == rrqueue)
			rrqueue = NULL ;
		else
			rrqueue->next = rrqueue->next->next ;
		free (c) ;
    }
    else fprintf (stderr, "tentative de vider une file vide");
}

/*
 * Q1.4 : Suppression d'un processus quelconque de la file
 * On suppose que le pcb existe forcement
 */

void queue_remove_any (struct pcb *p)
{
	int estrrqueue = (p == rrqueue->proc);
	if(rrqueue == NULL) return;

	struct cell * tmp = rrqueue;
	struct cell * tmp2;
	while(tmp->next->proc != p) tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp->next->next;
	free(tmp2->proc);
	free(tmp2);
	if(estrrqueue) 
		rrqueue = tmp->next;
}

/*
 * Q1.3 : Insertion du processus en fin de file
 */

void queue_insert (struct pcb *p)
{
	struct cell * c = (struct cell*) malloc(sizeof(struct cell));
	c->proc = p;
	struct cell * tmp = rrqueue;
	if(tmp == NULL)
		rrqueue = c;
	else
	{
		tmp = tmp->next;
		while(tmp->next != rrqueue) tmp = tmp->next;
		tmp->next = c;
	}
	c->next = rrqueue;
}

/*
 * Q1.5 : Affichage de la file
 */

void queue_display (void)
{
	if(rrqueue == NULL)
	{
		printf("Pas de file\n");
		return;
	}
	struct cell * tmp = rrqueue;
	printf("Premier dans la file : %d\n", rrqueue->proc->pid);
	tmp = rrqueue->next;
	while(tmp != rrqueue)
	{
		printf("pid : %d\n",tmp->proc->pid);
		tmp = tmp->next;
	}
}

/*
 * Q2.2 : Ordonnanceur selon l'algorithme du tourniquet
 */

//struct pcb *schedule (struct pcb *curproc)
//{
//    /* A ecrire */
//}
