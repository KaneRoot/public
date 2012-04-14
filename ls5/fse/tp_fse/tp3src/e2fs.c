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

	if(c->sb.s_magic != 0xEF53)
	{
		errno = -2;
		return NULL;
	}
	c->ngroups= 1 + ((c->sb.s_blocks_count - c->sb.s_first_data_block) / c->sb.s_blocks_per_group);

	c->gd = (struct ext2_group_desc *) malloc(sizeof( struct ext2_group_desc) * c->ngroups);

	lseek(c->fd, 2 * (1024 << c->sb.s_log_block_size), SEEK_SET);
	for( i = 0 ; i < c->ngroups ; i++)
	{
		if((read(c->fd, &(c->gd[i]), sizeof(struct ext2_group_desc))) == -1)
		{
			errno = -3;
			return NULL;
		}
		//printf("%d\n", c->gd[0].bg_block_bitmap);
	}

	/*		*/
	c->last = (struct buffer *) malloc(sizeof(struct buffer));
	struct buffer *tmp = c->last;
	for( i = 1 ; i < maxbuf ; i++)
	{
		tmp->next = (struct buffer *) malloc(sizeof(struct buffer));
		//tmp->data = malloc(1024 << c->sb.s_log_block_size);
		tmp->valid = i;
		tmp = tmp->next;
		tmp->next = NULL;
	}
	c->bufstat_read = 0;
	c->bufstat_cached = 0;
	return c;
}

void e2_ctxt_close (ctxt_t c)
{
	close(c->fd);
	free(c->gd);

	struct buffer * tmp;
	struct buffer * tmp2;

	tmp = c->last;
	while(c->last != NULL)
	{
		while(tmp->next != NULL)
			tmp = tmp->next;
		if(tmp->data != NULL)
			free(tmp->data);

		tmp2 = c->last;
		if(tmp2 != tmp)
		{
			while(tmp2->next != tmp)
				tmp2 = tmp2->next;
			tmp2->next = NULL;
		}
		else
			c->last = NULL;

		if(tmp != NULL)
			free(tmp);
		tmp = c->last;
	}

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

/******************************************************************************
 * Gestion du buffer et lecture bufferisee
 */

/* recupere un buffer pour le bloc, le retire de la liste des buffers
 * et lit le contenu si necessaire
 */
buf_t e2_buffer_get (ctxt_t c, pblk_t blkno)
{
	buf_t tmp = c->last;
	buf_t tmp2 = NULL;

	/* SI ON TROUVE */
	while(tmp->next != NULL && tmp->blkno != blkno)
		tmp = tmp->next;

	if(tmp->blkno == blkno && tmp->valid == 1 )
	{
		tmp2 = c->last;
		if(tmp2 != tmp)
		{
			while(tmp2->next != tmp)
				tmp2 = tmp2->next;
			tmp2->next = tmp->next;
		}
		else
		{
			c->last = tmp->next;
		}

		c->bufstat_cached++;
		return tmp;
	}

	/* SI ON NE TROUVE PAS */
	tmp = c->last;
	while(tmp->next != NULL)
		tmp = tmp->next;

	if(tmp->data != NULL)
	{
		free(tmp->data);
		tmp->data = NULL;
	}
	tmp->data = malloc(1024 << c->sb.s_log_block_size);

	if((e2_block_fetch(c, blkno, tmp->data)) == -1)
	{
		errno = -1;
		return NULL;
	}
	tmp->blkno = blkno;
	tmp->valid = 1;

	tmp2 = c->last;

	while(tmp2->next != tmp)
		tmp2 = tmp2->next;

	tmp2->next = tmp->next;
	tmp->next = NULL;

	c->bufstat_read++;
	return tmp;
}
        
/* replace le buffer en premier dans la liste */
void e2_buffer_put (ctxt_t c, buf_t b)
{
	b->next = c->last;
	c->last = b;
}
        
/* recupere les donnees du buffer */
void *e2_buffer_data (buf_t b)
{
	return b->data;
}

/* affiche les statistiques */
void e2_buffer_stats (ctxt_t c)
{
	printf("Le nombre de lectures sur disque %d\n", c->bufstat_read);
	printf("Le nombre de lecture dans le cache %d\n", c->bufstat_cached);
}

/******************************************************************************
 * Fonction de lecture d'un bloc dans un inode
 */

/* recupere le buffer contenant l'inode */
pblk_t e2_inode_to_pblk (ctxt_t c, inum_t i)
{
	int nb_inodes_par_groupe = c->sb.s_inodes_per_group;
//	printf("Nombre d'inodes par groupe : %d\n", nb_inodes_par_groupe);

	int numero_groupe_bloc = (i-1)/nb_inodes_par_groupe;
//	printf("Numéro de groupe de bloc : %d\n", numero_groupe_bloc);

	int nombre_inodes_par_bloc = (1024 << c->sb.s_log_block_size) / sizeof(struct ext2_inode);
//	printf("Nombre d'inodes par bloc : %d\n", nombre_inodes_par_bloc);

	int num_bloc = c->gd[numero_groupe_bloc].bg_inode_table + ((i-1) % nb_inodes_par_groupe) / nombre_inodes_par_bloc;
//	printf("bg bidule : %d\n", c->gd[numero_groupe_bloc].bg_inode_table);
//	printf("Numéro de bloc : %d\n", num_bloc);

	return num_bloc;
}

/* extrait l'inode du buffer */
struct ext2_inode *e2_inode_read (ctxt_t c, inum_t i, buf_t b)
{
	struct ext2_inode * inode = malloc(sizeof(struct ext2_inode));
	if( memcpy(inode, (b->data + (((i-1)%(1024 << c->sb.s_log_block_size)/sizeof(struct ext2_inode)) * sizeof(struct ext2_inode))), sizeof(struct ext2_inode)) == -1)
	{
		errno = 1;
		free(inode);
		return (struct ext2_inode*) NULL;
	}

	return inode;
}

/* numero de bloc physique correspondant au bloc logique blkno de l'inode in */
pblk_t e2_inode_lblk_to_pblk (ctxt_t c, struct ext2_inode *in, lblk_t blkno)
{
	return 0;
}

