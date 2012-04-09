#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>

#include "e2fs.h"

#define	MAXBUF	100
struct context
{
    int fd ;
    struct ext2_super_block sb ;
    int ngroups ;			/* nombre de groupes dans gd [] */
    struct ext2_group_desc *gd ;	/* c'est un tableau */
    /* ce qui suit concerne les lectures bufferisees */
    struct buffer *last ;		/* pointe sur dernier buffer */
    int bufstat_read ;			/* nombre de demandes de lecture */
    int bufstat_cached ;		/* nombre de lectures en cache */
} ;

/* Lit un bloc physique quelconque (sans passer par les buffers) */

/* alloue un contexte, alloue une zone de données suffisamment grande pour contenir un bloc, lit le bloc dont le numéro est fourni en argument, l’affiche sur la sortie standard, et désalloue le contexte avant de sortir. */
int main (int argc, char *argv [])
{
    ctxt_t c ;

    if (argc != 3)
    {
		fprintf (stderr, "usage: %s fs blkno\n", argv [0]) ;
		exit (1) ;
    }

    c = e2_ctxt_init (argv [1], MAXBUF) ;
    if (c == NULL)
    {
		perror ("e2_ctxt_init") ;
		exit (1) ;
    }

	printf("Nombre de blocks : %d\n", c->sb.s_blocks_count);
	printf("Nombre de blocks par groupes : %d\n", c->sb.s_blocks_per_group);
	printf("Nombre de groupes : %d\n", c->ngroups);
	printf("c->gd.bg_used_dirs_count %d\n", c->gd[0].bg_used_dirs_count);
    /* A REDIGER */

    e2_ctxt_close (c) ;

    exit (0) ;
}
