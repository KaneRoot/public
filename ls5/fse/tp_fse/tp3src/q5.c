#include <stdio.h>
#include <stdlib.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Affiche le fichier reference par l'inode avec l'"ouverture de fichier" */

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

    /* A REDIGER */
	file_t fichier = e2_file_open(c, atoi(argv[2]));

	int car = 0;
	while((car = e2_file_getc(fichier)) != EOF)
		printf("%c",(char) car);

	e2_file_close(fichier);
    e2_ctxt_close (c) ;

    exit (0) ;
}
