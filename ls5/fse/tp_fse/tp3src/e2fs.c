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
	}

	/*		*/
	c->last = (struct buffer *) malloc(sizeof(struct buffer));
	struct buffer *tmp = c->last;
	for( i = 0 ; i < maxbuf ; i++)
	{
		tmp->valid = 0;
		tmp->blkno = 0;
		tmp->data = NULL;
		if(i != maxbuf - 1)
		{
			tmp->next = (struct buffer *) malloc(sizeof(struct buffer));
			tmp = tmp->next;
		}
		tmp->next = NULL;
	}

	// Bon ok c'est pour la forme ça.
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
	buf_t tmp2 = c->last;

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

/* recupere le numéro du bloc contenant l'inode */
pblk_t e2_inode_to_pblk (ctxt_t c, inum_t i)
{
	int nb_inodes_par_groupe = c->sb.s_inodes_per_group;

	int numero_groupe_bloc = (i-1)/nb_inodes_par_groupe;

	int nombre_inodes_par_bloc = (1024 << c->sb.s_log_block_size) / sizeof(struct ext2_inode);

	int num_bloc = c->gd[numero_groupe_bloc].bg_inode_table + ((i-1) % nb_inodes_par_groupe) / nombre_inodes_par_bloc;

	return num_bloc;
}

/* extrait l'inode du buffer */
struct ext2_inode *e2_inode_read (ctxt_t c, inum_t i, buf_t b)
{
	if(b->data == NULL)
	{
		printf("LE BLOC DATA EST NULL\n");
	}

	int nombre_inodes_par_bloc = (1024 << c->sb.s_log_block_size) / sizeof(struct ext2_inode);
	struct ext2_inode * inode = malloc(sizeof(struct ext2_inode));
	memcpy(inode, 
			(b->data + ((i-1) % nombre_inodes_par_bloc) * sizeof(struct ext2_inode)),
			sizeof(struct ext2_inode));

	return inode;
}
/* numero de bloc physique correspondant au bloc logique blkno de l'inode in */
pblk_t e2_inode_lblk_to_pblk (ctxt_t c, struct ext2_inode *in, lblk_t blkno)
{
	int taille_bloc = (1024 << c->sb.s_log_block_size);
	int nb_blocs_max = 12 + taille_bloc + taille_bloc * taille_bloc + taille_bloc * taille_bloc * taille_bloc;

	/* Assez clairement, si blkno > au nb max de blocs pour un fichier, il y a un soucis */
	if(blkno > nb_blocs_max || blkno > in->i_blocks)
	{
		return 0;
	}
	if( blkno < 12)
		return in->i_block[blkno];
	else if ( blkno < taille_bloc + 11)
	{
		void * data = malloc(taille_bloc); 
		if( e2_block_fetch(c, in->i_block[13], data) != 0)
		{
			   errno = 1;
			   return 0;
		}
		int info ;
		memcpy(&info, (data + blkno-12), sizeof(int));

		free(data);

		return info;
	}
	else if ( blkno < (taille_bloc*taille_bloc) + 11)
	{
	}

	return 0;
}

/******************************************************************************
 * Operation de haut niveau : affichage d'un fichier complet
 */

/* affiche les blocs d'un fichier */
int e2_cat (ctxt_t c, inum_t i, int disp_pblk)
{
	int num_bloc, j;
	buf_t b, tmp;
	struct ext2_inode *inode;

	num_bloc = e2_inode_to_pblk(c, i);
	b = e2_buffer_get(c, num_bloc);
	e2_buffer_put(c, b);
	inode = e2_inode_read(c, i, b);

	if(disp_pblk == 0)
	{
		for(j = 0 ; e2_inode_lblk_to_pblk(c, inode, j) != 0 ; j++)
		{
			tmp = e2_buffer_get(c, e2_inode_lblk_to_pblk(c, inode, j));
			e2_buffer_put(c, tmp);
			printf("%s", (char *)e2_buffer_data(tmp));
		}
	}
	else
	{
		printf("La taille du fichier est de : %d\n", inode->i_size);
		printf("L'entrée i_blocks est de : %d\n", inode->i_blocks);
		printf("Les blocs : \t");
		for(j = 0 ; e2_inode_lblk_to_pblk(c, inode, j) != 0 ; j++)
		{
			printf("%d, ", e2_inode_lblk_to_pblk(c, inode, j));
		}
		printf("\n");
	}

	free(inode);
	return 0;
}

/******************************************************************************
 * Simulation d'une ouverture de fichiers
 */

file_t e2_file_open (ctxt_t c, inum_t i)
{
	file_t fichier = (file_t) malloc(sizeof(struct ofile));
	//int taille_bloc = (1024 << c->sb.s_log_block_size);
	int num_pblk_inode;
	buf_t b;

	//fichier->data = (char *) malloc(taille_bloc);

	if( 0 == (num_pblk_inode = e2_inode_to_pblk(c, i)))
		return (file_t) NULL;

	if( NULL == (b = e2_buffer_get(c, num_pblk_inode)))
		return (file_t) NULL;

	e2_buffer_put(c, b);

	fichier->ctxt = c;
	fichier->buffer = b;

	if(0 == (fichier->inode = e2_inode_read(c, i, b)))
		return (file_t) NULL;

	//memcpy(fichier->data, (char *) e2_buffer_data(b), taille_bloc);
	fichier->data = NULL;
	fichier->len = fichier->inode->i_size;
	fichier->pos = 0;
	fichier->curblk = 0;

	return fichier;
}

void e2_file_close (file_t of)
{
	if(of->data != NULL)
		free(of->data);

	free(of->inode);
	free(of);
}

/* renvoie EOF ou un caractere valide */
int e2_file_getc (file_t of)
{
	int taille_bloc = (1024 << of->ctxt->sb.s_log_block_size);
	int car;
	buf_t b;

	if(of->len == of->pos)
		return EOF;

	if( (of->pos % taille_bloc) == 0 || of->pos == 0)
	{
		if(of->pos != 0)
			of->curblk++;
	//	printf("\nChangement de bloc : %d\n", of->curblk);
		if(of->data != NULL)
			free(of->data);

		b = e2_buffer_get(of->ctxt, e2_inode_lblk_to_pblk(of->ctxt, of->inode, of->curblk ));
		e2_buffer_put(of->ctxt, b);

		of->data = (char *) malloc(taille_bloc);
		memcpy(of->data, e2_buffer_data(b), taille_bloc);
	}

	//printf("%d - %d \n", of->pos, of->curblk);
	memcpy(&car, of->data + (of->pos % taille_bloc), sizeof(char));
	//car = *(of->data + (of->pos % taille_bloc)) & 0xFF;
	of->pos++;
	return car;
}

/* renvoie nb de caracteres lus (0 lorsqu'on arrive en fin de fichier) */
int e2_file_read (file_t of, void *data, int len)
{
	// nombre de caractères lus
	int i = 0;
	int c ;
	while( i != len && (c = e2_file_getc(of)) != EOF)
	{
		*((char *)data + i) = (char) c;
		i++;
	}

	return i;
}

/******************************************************************************
 * Operations sur les repertoires
 */

/* retourne une entree de repertoire */
struct ext2_dir_entry_2 *e2_dir_get (file_t of)
{
	buf_t b;
	int taille, taille_du_nom;
	char * lenom = malloc(500);

	static struct ext2_dir_entry_2 * entree;
	static int e2_dir_get_offset = 0;

	b = e2_buffer_get(of->ctxt, of->inode->i_block[0]);
	e2_buffer_put(of->ctxt, b);

	if(0 == S_ISDIR(of->inode->i_mode))
	{
		/*	Ce n'est pas un répertoire	*/
		return (struct ext2_dir_entry_2 *) NULL;
	}
	/*	C'est bien un répertoire	*/

	memcpy(&taille, (b->data + e2_dir_get_offset + 4), sizeof(char)*2);
	if(taille != 0 && entree != NULL)
	{
		if(entree != NULL)
		{
			free(entree);
			entree = malloc(taille);
		}
		memcpy(entree, (b->data + e2_dir_get_offset), taille);
		memcpy(&taille_du_nom, (b->data + e2_dir_get_offset + 6 ), 1);
	}
	e2_dir_get_offset += taille;

	printf("La taille %d - taille du nom : %d\n", taille, taille_du_nom);
	snprintf(lenom, taille_du_nom, "%s", entree->name);
	printf("Le nom : %s\n", lenom);

	free(lenom);
	return (struct ext2_dir_entry_2 *) entree;
}

/* recherche un composant de chemin dans un repertoire */
//inum_t e2_dir_lookup (ctxt_t c, inum_t i, char *str, int len)
//{
//	return (inum_t) NULL;
//}
//
