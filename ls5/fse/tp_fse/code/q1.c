#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>
#include "errno.h"

#include "e2fs.h"

#define	MAXBUF	100

/* Lit un bloc physique quelconque (sans passer par les buffers) */

/* alloue un contexte, alloue une zone de données suffisamment grande pour contenir un bloc, lit le bloc dont le numéro est fourni en argument, l’affiche sur la sortie standard, et désalloue le contexte avant de sortir. */
int main (int argc, char *argv [])
{
    ctxt_t c ;
	void * bloc = NULL;
	char * str = NULL;

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

	/*	Voici quelques affichages que je faisais pour faire des tests au début
	 *	Je les laisse volontairement pour plus tard, m'en souvenir.
	 *

	printf("Nombre de blocks : %d\n", c->sb.s_blocks_count);
	printf("Nombre de blocks par groupes : %d\n", c->sb.s_blocks_per_group);
	printf("Nombre de groupes : %d\n", c->ngroups);
	printf("Taille d'un bloc : %d\n", 1024 << c->sb.s_log_block_size);
	printf("c->gd.bg_used_dirs_count %d\n", c->gd[0].bg_used_dirs_count);

	*/

	bloc = malloc(e2_ctxt_blksize(c));
	if(bloc == NULL)
	{
		fprintf(stderr, "Impossible de faire un malloc\n");
		e2_ctxt_close(c);
		exit(1);
	}
	
	str = malloc(e2_ctxt_blksize(c) + 1);
	if(str == NULL)
	{
		fprintf(stderr, "Impossible de faire un malloc\n");
		free(bloc);
		e2_ctxt_close(c);
		exit(2);
	}

	if((e2_block_fetch(c, atoi(argv[2]), bloc)) == 0)
	{
		fprintf(stderr, "Numéro d'erreur : %d\n", errno);
		free(str);
		free(bloc);
		e2_ctxt_close(c);
		exit(3);
	}

	snprintf(str, e2_ctxt_blksize(c), "%s", (char *) bloc);
	printf("%s\n", str);

	/* désallocations */
	free(bloc);
	free(str);
    e2_ctxt_close (c) ;

    exit (0) ;
}
