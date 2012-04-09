#include <stdio.h>
#include <stdlib.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "e2fs.h"

struct buffer
{
    void *data ;			/* les donnees du bloc */
    pblk_t blkno ;			/* numero de bloc physique */
    int valid ;				/* donnees valides */
    struct buffer *next ;
} ;

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

struct ofile
{
    struct context *ctxt ;		/* eviter param a chaque e2_file_xxx */
    struct buffer *buffer ;		/* buffer contenant l'inode */
    struct ext2_inode *inode ;		/* l'inode proprement dit */
    lblk_t curblk ;			/* position en bloc */
    char *data ;			/* donnees */
    int len ;				/* longueur utile dans les donnees */
    int pos ;				/* position dans les donnees */
} ;

/******************************************************************************
 * Initialisation du contexte
 */

ctxt_t e2_ctxt_init (char *file, int maxbuf)
{
	ctxt_t c = (ctxt_t) malloc(sizeof(struct context));
	int i;


	c->fd = open(file, O_RDONLY);

	lseek(c->fd, 0x400, SEEK_SET);
	if((read(c->fd, &(c->sb), sizeof(struct ext2_super_block))) == -1)
	{
		errno = -1;
		return NULL;
	}

	//printf("Magik number : %d, le bon : %d\n", c->sb.s_magic, 0xEF53);
	if(c->sb.s_magic != 0xEF53)
	{
		errno = -2;
		return NULL;
	}
	c->ngroups = 1 + (c->sb.s_blocks_count / c->sb.s_blocks_per_group);

	c->gd = (struct ext2_group_desc *) malloc(sizeof( struct ext2_group_desc) * c->ngroups);

	for( i = 0 ; i < c->ngroups ; i++)
	{
		if((read(c->fd, &(c->gd[i]), sizeof(struct ext2_group_desc))) == -1)
		{
			errno = -3;
			return NULL;
		}
	}

	return c;
}

void e2_ctxt_close (ctxt_t c)
{
	close(c->fd);
	free(c);
}

int e2_ctxt_blksize (ctxt_t c)
{
	return (c->sb.s_blocks_count - c->sb.s_first_data_block)/c->sb.s_blocks_per_group;
}

/******************************************************************************
 * Fonctions de lecture non bufferisee d'un bloc
 */

int e2_block_fetch (ctxt_t c, pblk_t blkno, void *data)
{
	int n = 0;
	blkno -= 2;
	if((lseek(c->fd, 2048 + (blkno *(1024 << c->sb.s_log_block_size)), SEEK_SET)) == -1)
	{
		errno = -1;
		return -1;
	}
	if((n = read(c->fd, data, (1024 << c->sb.s_log_block_size))) == -1)
	{
		errno = -2;
		return -1;
	}

	return 0;
}
