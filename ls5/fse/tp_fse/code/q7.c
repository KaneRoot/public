#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Affiche le fichier ou le repertoire reference par l'inode */

int main (int argc, char *argv [])
{
    ctxt_t c ;
	int retour = 0;
	inum_t numero_inode;

    if (argc != 3)
    {
		fprintf (stderr, "usage: %s fs chemin\n", argv [0]) ;
		exit (1) ;
    }

    c = e2_ctxt_init (argv [1], MAXBUF) ;
    if (c == NULL)
    {
		perror ("e2_ctxt_init") ;
		exit (1) ;
    }

    /* A REDIGER */

	numero_inode = e2_namei(c, argv[2]);
	if(numero_inode == 0)
	{
		if(errno == -1)
		{
			printf("L'objet n'a pas été trouvé\n");
			e2_ctxt_close(c);
			exit( 1 );
		}
	}
	else
	{
		retour = e2_ls(c, numero_inode);

		/* si ce n'est pas un répertoire */
		if(retour == -1)
		{
			retour = e2_cat(c, numero_inode, 0);
		}
	}

	e2_ctxt_close (c) ;

    exit (0) ;
}
