#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simul.h"

/*
 * Q1.2 : Creation d'un nouveau processus
 */
struct pcb *pcb_create (int pid, int start, int duration, int prio)
{
	struct pcb *p = (struct pcb*) malloc(sizeof(struct pcb));
	p->pid = pid;
	p->start_time = start;
	p->duration = duration;
	p->prio = prio;
	p->cpu_time = 0;
}

/*
 * Suppression d'un processus
 */

void pcb_destroy (struct pcb *pcb)
{
    free (pcb) ;
}
