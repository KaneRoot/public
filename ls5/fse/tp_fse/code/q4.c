#include <stdio.h>
#include <stdlib.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Affiche le fichier reference par l'inode avec e2_cat */

int main (int argc, char *argv [])
{
    ctxt_t c ;
	int dispblkno;
	int retour; 

    if (argc != 3 && argc != 4)
    {
		fprintf (stderr, "usage: %s fs inode [dispblkno]\n", argv [0]) ;
		exit (1) ;
    }

    c = e2_ctxt_init (argv [1], MAXBUF) ;
    if (c == NULL)
    {
		perror ("e2_ctxt_init") ;
		exit (1) ;
    }

	/* par défaut dispblkno = 0 */
	dispblkno = 0;

	/* si on a entré une valeur */
	if(argc == 4)
		dispblkno = atoi(argv[3]);

	retour = e2_cat(c, atoi(argv[2]), dispblkno);
	if( -1 == retour )
	{
		fprintf(stderr, "Erreur : inode < 0 \n");
	}
	else if ( -2 == retour)
	{
		fprintf(stderr, "Erreur : buffer vide\n");
	}

    e2_ctxt_close (c) ;

    exit (0) ;
}
