#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>

int main (int argc, char *argv [])
{
	int fd ;
	struct ext2_super_block sb ;
	printf ("Taille du super-bloc %d\n", sizeof (struct ext2_super_block)) ;
	printf ("Taille d’une inode : %d\n", sizeof (struct ext2_inode)) ;

	if ((fd = open ("tp3.ext2", O_RDONLY)) == -1) {
		perror ("open") ;
		exit (1) ;
	}
	lseek (fd, 0x400, SEEK_SET) ;
	if ((read (fd, &sb, sizeof(struct ext2_super_block))) == -1) {
		perror ("read") ;
		exit (1) ;
	}
	printf("Nombre d’inodes : %d\n", sb.s_inodes_count) ;
	printf("Nombre de blocs : %d\n", sb.s_blocks_count) ;
	printf("Taille d’un bloc : %d\n", EXT2_BLOCK_SIZE (&sb)) ;
	printf("Premier inode libre : %d\n", sb.s_first_ino) ;
	
	exit (0) ;
}

void quitter(char * error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
