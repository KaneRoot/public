#include <stdio.h>
#include <stdlib.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Affiche le repertoire reference par l'inode */

int main (int argc, char *argv [])
{
    ctxt_t c ;

    if (argc != 3)
    {
		fprintf (stderr, "usage: %s fs inode\n", argv [0]) ;
		exit (1) ;
    }

    c = e2_ctxt_init (argv [1], MAXBUF) ;
    if (c == NULL)
    {
		perror ("e2_ctxt_init") ;
		exit (1) ;
    }

	if(e2_ls(c, atoi(argv[2])) != 0)
	{
		fprintf(stdout, "Erreur - inode %d bien un répertoire ?\n", atoi(argv[2]));
	}

    e2_ctxt_close (c) ;

    exit (0) ;
}
