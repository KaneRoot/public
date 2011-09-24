#include "tp1.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUF_GETCHAR2 10 // pour getchar2 

int main(int argc, char * argv[])
{
	//printf("EOF : %d\n",EOF);
	//test_getchar1();
	//test_getchar2();
	mystat(argc,argv);
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
void mystat(int argc, char * argv[])
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
	char * ligne = NULL;
	struct stat stat_buf;

	if((stat(nom_du_fichier,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE); 
	}

	ligne = malloc(sizeof(char) * 150);

	/* Affichage du type */
	switch (stat_buf.st_mode & S_IFMT) 
	{
		case S_IFBLK:	strcat(ligne,"b");	break;
		case S_IFCHR:	strcat(ligne,"c");	break;
		case S_IFDIR:	strcat(ligne,"d");	break;
		case S_IFIFO:	strcat(ligne,"p");	break;
		case S_IFLNK:	strcat(ligne,"l");	break;
		case S_IFREG:	strcat(ligne,"-");	break;
		case S_IFSOCK:	strcat(ligne,"s");	break;
		default:		strcat(ligne,"u");	break;
	}

	/* Affichage des droits */
	(stat_buf.st_mode & S_IRUSR) ? strcat(ligne,"r") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IWUSR) ? strcat(ligne,"w") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IXUSR) ? strcat(ligne,"x") : strcat(ligne,"-");

	(stat_buf.st_mode & S_IRGRP) ? strcat(ligne,"r") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IWGRP) ? strcat(ligne,"w") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IXGRP) ? strcat(ligne,"x") : strcat(ligne,"-");

	(stat_buf.st_mode & S_IROTH) ? strcat(ligne,"r") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IWOTH) ? strcat(ligne,"w") : strcat(ligne,"-");
	(stat_buf.st_mode & S_IXOTH) ? strcat(ligne,"x") : strcat(ligne,"-");

	strcat(ligne, " ");
	strcat(ligne, nom_du_fichier);

	printf("%s\n",strcat(ligne,"\0"));
	free(ligne);
}
