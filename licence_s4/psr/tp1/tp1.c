#include "tp1.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

#define TAILLE_CHAINE 150
#define MAXBUF_GETCHAR2 10 // pour getchar2 
#define LEXIQUE "lexique"

int main(int argc, char * argv[])
{
	//printf("EOF : %d\n",EOF);
	//test_getchar1();
	//test_getchar2();
	//test_print_ls(argc,argv);
	//test_liste_rep(argc,argv);
	//lecture_entree_standard_fonctions_bibliotheque();
	//lecture_entree_standard_primitives_systeme(512);
	test_recherche_dichotomique();	
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
	char * emplacement = NULL;

	if((repertoire = opendir(nom_repertoire)) == NULL)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	while((element = readdir(repertoire)))
	{
		if(element->d_name[0] == '.')
			continue;
		emplacement = malloc(sizeof(char) * TAILLE_CHAINE);
		strncpy(emplacement, nom_repertoire, strlen(nom_repertoire));
		if(emplacement[strlen(nom_repertoire) - 1] != '/')
			emplacement[strlen(nom_repertoire)] = '/';
		strcat(emplacement, element->d_name);
		print_ls(emplacement);
		vider_chaine(emplacement);
		emplacement = NULL;
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
/* Sans ça, emplacement ne se vide pas correctement */
void vider_chaine(char * chaine)
{
	int i;
	for(i = 0 ; i < strlen(chaine) ; i++)
		chaine[i] = '\0';
}
void lecture_entree_standard_fonctions_bibliotheque()
{
	int c;
	while((c = getchar()) != EOF)
		putchar((char) c);
	printf("\n");
}
void lecture_entree_standard_primitives_systeme(int taille_buffer)
{
	int n;
	char * c = malloc(sizeof(char) * taille_buffer);
	while(( n = read(0, c, taille_buffer)) != 0 )
		write(1,c,n);
	free(c);
	printf("\n");
}
int recherche_dichotomique(char * nom_a_chercher)
{
	int retour = 0,fd,taille_fichier;
	char * lexique = LEXIQUE;
	struct stat stat_buf;

	if((stat(lexique,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE); 
	}

	taille_fichier = stat_buf.st_size;
	printf("TAILLE FICHIER : %d \n",taille_fichier);

	if((fd = open(lexique,O_RDONLY)) <=0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	close(fd);
	return retour;
}
void test_recherche_dichotomique()
{
	int n = 0;
	char buf[6];
	while((n = read(0,buf,5)) != 0)
	{
		if(recherche_dichotomique(buf))
			printf("Ce mot existe dans le lexique : %s\n",buf);
		else
			printf("Ce mot n'existe pas dans le lexique : %s\n",buf);
	}
}
