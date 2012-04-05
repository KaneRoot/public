#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "e2fs.h"

#define	MAXBUF	100

/* Lit un bloc physique quelconque (sans passer par les buffers) */

/* Cette fonction alloue un contexte, lit le super-bloc, vérifie la signature (champ s_magic), lit les descripteurs de groupes. Le paramètre maxbuf n’est pour l’instant pas utilisé (il servira dans le chapitre suivant). Vous noterez que la taille des blocs n’est pas une constante, mais est indiquée dans le super-bloc. En cas d’erreur, la valeur NULL est renvoyée et la variable errno doit indiquer la raison.  */
ctxt_t e2_ctxt_init (char *file, int maxbuf)
{
	ctxt_t b;
	return b;
}

// Désalloue un contexte
void e2_ctxt_close (ctxt_t c)
{
}

// Cette fonction renvoie la taille des blocs du système de fichiers.
int e2_ctxt_blksize (ctxt_t c)
{
	return 0;
}
/* Cette fonction lit un bloc sur le système de fichiers, place à l’adresse fournie par data (qu’on suppose déjà allouée par l’appelant) les données du bloc, et renvoie 1 si tout s’est bien passé. Le numéro de bloc à lire est indiqué par le paramètre blkno. En cas d’erreur, la valeur 0 est renvoyée et la variable errno doit indiquer la raison. */
int e2_block_fetch (ctxt_t c, pblk_t blkno, void *data)
{
	return 0;
}
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

    /* A REDIGER */

    e2_ctxt_close (c) ;

    exit (0) ;
}
