#include "tp1.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define MAXBUF_GETCHAR2 10 // pour getchar2 

int main(int argc, char * argv[])
{
	//printf("EOF : %d\n",EOF);
	//test_getchar1();
	//test_getchar2();
	//test_print_ls(argc,argv);
	test_liste_rep(argc,argv);
	return EXIT_SUCCESS;
}
void test_getchar2()
{
	int c;
	while((c = getchar2()) != EOF)
		putchar(c);
}
int getchar2(void)
{
	static char buf[MAXBUF_GETCHAR2];
	static int indice = 0;
	static int taille = 0;
	if(indice == 0 || indice >= (taille ))
	{
		taille = read(0, buf, MAXBUF_GETCHAR2);
		if(taille == 0)
			buf[0] = EOF;
		indice = 0;
	}
	indice++;
	return (int) buf[indice - 1];
}
void test_getchar1()
{
	int c;
	while((c = getchar1()) != EOF)
		putchar(c);
}
int getchar1(void)
{
	int n;
	char c;
	n = read(0, &c, 1);
	if(n == 1)
		return (int) c;
	return EOF;
}
void test_print_ls(int argc, char * argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "USAGE : %s file\n",argv[0]); 
		exit(EXIT_FAILURE); 
	}
	print_ls(argv[1]);
}
void print_ls(char * nom_du_fichier)
{
	struct stat stat_buf;

	if((stat(nom_du_fichier,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE); 
	}

	/* Affichage du type */
	switch (stat_buf.st_mode & S_IFMT) 
	{
		case S_IFBLK:	printf("b");	break;
		case S_IFCHR:	printf("c");	break;
		case S_IFDIR:	printf("d");	break;
		case S_IFIFO:	printf("p");	break;
		case S_IFLNK:	printf("l");	break;
		case S_IFREG:	printf("-");	break;
		case S_IFSOCK:	printf("s");	break;
		default:		printf("u");	break;
	}

	/* Affichage des droits */
	(stat_buf.st_mode & S_IRUSR) ? printf("r") : printf("-");
	(stat_buf.st_mode & S_IWUSR) ? printf("w") : printf("-");
	(stat_buf.st_mode & S_IXUSR) ? printf("x") : printf("-");

	(stat_buf.st_mode & S_IRGRP) ? printf("r") : printf("-");
	(stat_buf.st_mode & S_IWGRP) ? printf("w") : printf("-");
	(stat_buf.st_mode & S_IXGRP) ? printf("x") : printf("-");

	(stat_buf.st_mode & S_IROTH) ? printf("r") : printf("-");
	(stat_buf.st_mode & S_IWOTH) ? printf("w") : printf("-");
	(stat_buf.st_mode & S_IXOTH) ? printf("x") : printf("-");

	printf(" %s\n",nom_du_fichier);

}
void liste_rep(char * nom_repertoire)
{
	DIR * repertoire;
	struct dirent * element;

	if((repertoire = opendir(nom_repertoire)) == NULL)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	while((element = readdir(repertoire)))
	{
		print_ls(element->d_name);
	}
	closedir(repertoire);
}
void test_liste_rep(int argc, char * argv[])
{
	int i;
	if(argc < 2)
	{
		fprintf(stderr, "USAGE : %s dir [ dir ... ]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	for(i = 1 ; i < argc ; i++)
	{
		if(is_dir(argv[i]))
			liste_rep(argv[i]);
		else
			printf("%s n'est pas un répertoire\n", argv[i]);
	}
}
int is_dir(char * nom)
{
	int res;
	struct stat stat_buf;

	if((stat(nom,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE); 
	}
	switch (stat_buf.st_mode & S_IFMT) 
	{
		case S_IFDIR:	
			res = 1;
			break;
		default:
			res = 0;	
			break;
	}
	return res;
}
