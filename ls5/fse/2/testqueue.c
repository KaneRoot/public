#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simul.h"
#include "testqueue.h"

int main(int argc, char * argv[])
{
	int i;
	struct pcb * p1[3];
	struct pcb * p2[3];

	for(i = 0 ; i < 3 ; i++)
		p1[i] = pcb_create(i+1, i, i, 0);
	for(i = 0 ; i < 3 ; i++)
		p2[i] = pcb_create(i+4, i, i, 0);

	queue_init();
	for(i = 0 ; i < 3 ; i++)
		queue_insert(p1[i]);
	queue_display();
	for(i = 0 ; i < 3 ; i++)
		queue_insert(p2[i]);
	queue_display();

	
	return EXIT_SUCCESS;
}

