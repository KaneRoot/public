#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>
#include "errno.h"

#include "e2fs.h"

#define	MAXBUF	10

/* Lit un bloc physique quelconque en passant par un buffer */

int main (int argc, char *argv [])
{
	int i;
    ctxt_t c ;

    if (argc < 3)
    {
		fprintf (stderr, "usage: %s fs blkno ... blkno\n", argv [0]) ;
		exit (1) ;
    }

    c = e2_ctxt_init (argv [1], MAXBUF) ;
    if (c == NULL)
    {
		perror ("e2_ctxt_init") ;
		exit (1) ;
    }

    /* A REDIGER */

	for( i = 2 ; i < argc ; i++)
		e2_buffer_put(c, e2_buffer_get(c, atoi(argv[i])));

	for( i = 2 ; i < argc ; i++)
		e2_buffer_put(c, e2_buffer_get(c, atoi(argv[i])));

	e2_buffer_stats(c);
    e2_ctxt_close (c) ;

    exit (0) ;
}
