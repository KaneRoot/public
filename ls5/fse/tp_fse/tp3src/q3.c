#include <stdio.h>
#include <stdlib.h>

#include <linux/fs.h>
#include <linux/ext2_fs.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Affiche le numero de bloc de l'inode n et la taille du fichier */

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

    e2_ctxt_close (c) ;

    exit (0) ;
}
