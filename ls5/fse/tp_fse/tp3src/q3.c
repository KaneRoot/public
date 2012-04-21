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

	pblk_t num_bloc = e2_inode_to_pblk(c, atoi(argv[2]));
	printf("Numéro de bloc : %d\n", num_bloc);
	buf_t b = e2_buffer_get(c, num_bloc);
	e2_buffer_put(c, b);

	struct ext2_inode * inode;

	if( (inode = e2_inode_read(c, atoi(argv[2]), b)) == NULL)
	{
		printf("Il ya eu une erreur\n");
		exit(1);
	}

	printf("Taille du fichier : %d\n", inode->i_size);

	free(inode);
	e2_ctxt_close (c) ;

    exit (0) ;
}
