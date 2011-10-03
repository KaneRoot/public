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
#include <ctype.h>

#define TAILLE_CHAINE 150
#define MAXBUF_GETCHAR2 10 // pour getchar2 
#define LEXIQUE "lexique"
#define TAILLE_LIGNES 9
#define TAILLE_BUFFER_DERNIER_CAR 10

int main(int argc, char * argv[])
{
	//printf("EOF : %d\n",EOF);
	//test_getchar1();
	//test_getchar2();
	//test_print_ls(argc,argv);
	//test_liste_rep(argc,argv);
	//lecture_entree_standard_fonctions_bibliotheque();
	//lecture_entree_standard_primitives_systeme(512);
	//test_recherche_dichotomique();	
	//print_derniers_car_simple(argv[1]);
	mon_tolower(argv[1]);

	return EXIT_SUCCESS;
}
void test_getchar2()
{
	int c;
	while((c = correction_getchar()) != EOF)
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
			emplacement[strlen(nom_repertoire)]= '/';
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
	struct stat stat_buf;

	if((stat(nom,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE); 
	}
	return (stat_buf.st_mode & S_IFDIR) ? 1 : 0; 
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
int correction_getchar()
{
	static char correction_getchar_buffer[MAXBUF_GETCHAR2];
	static int ncar = 0;
	static int correction_getchar_indice;

	if(ncar == 0)
	{
		ncar = read(0,correction_getchar_buffer,MAXBUF_GETCHAR2);
		correction_getchar_indice = 0;
	}
	return (ncar-- > 0) ? correction_getchar_buffer[correction_getchar_indice++] : EOF;
}
int recherche_dichotomique(char * nom_a_chercher)
{
	/*
	 *
	int fd,taille_fichier, nb_lignes,trouve = 0,ecart;
	int car_lus, retour_strcmp;
	int ligne_courante, ligne_precedente,ligne_precedente2;
	char buffer[5];
	char * lexique = LEXIQUE;
	struct stat stat_buf;

	if((stat(lexique,&stat_buf)) == -1)
	{	
		perror("stat");		
		exit(EXIT_FAILURE);
	}

	taille_fichier = stat_buf.st_size;
	printf("TAILLE FICHIER : %d \n",taille_fichier);
	nb_lignes = taille_fichier / TAILLE_LIGNES;
	printf("nombre de lignes : %d \n", nb_lignes);


	if((fd = open(lexique,O_RDONLY)) <= 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	ecart = nb_lignes / 2;
	ligne_suivante = nb_lignes / 2;
	while(ligne_suivante != ligne_precedente || trouve)
	{
		if((lseek(fd,ligne_suivante * TAILLE_LIGNES + 1, SEEK_SET)) < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if((car_lus = read(fd, buffer, 5)) < 0)
		{
			perror("Impossible de lire les 5 caractères");
			exit(EXIT_FAILURE);
		}
		else if (car_lus == 5)
		{
			retour_strcmp = strcmp(nom_a_chercher,buffer);
			if( retour_strcmp == 0 ) 
				trouve = 1;
			else if (retour_strcmp < 0)
			{
				ligne_suivante = ligne_suivante - ecart;
			}
			else
			{
				ligne_suivante = ligne_suivante + ecart;
			}
		}
		ecart = (ecart <= 1) ? 1 : ecart / 2;

	}

	close(fd);
	return trouve;
	 *
	*/
	return 0;
}
void test_recherche_dichotomique()
{
	/*
	 *
	int n = 0;
	char buf[6];
	buf[5] = '\0';
	while((n = read(0,buf,5)) != 0)
	{
		if(recherche_dichotomique(buf))
			printf("Ce mot existe dans le lexique : %s\n",buf);
		else
			printf("Ce mot n'existe pas dans le lexique : %s\n",buf);
	}
	 *
	*/
	printf("non implantée : %s\n", __func__);

}
void print_derniers_car(char * nom_du_fichier)
{
	int fd, n, i, premiere_fois = 0;
	char buffer[TAILLE_BUFFER_DERNIER_CAR];
	char chaine_finale[TAILLE_BUFFER_DERNIER_CAR + 1];
	if((fd = open(nom_du_fichier, O_RDONLY)) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	while(( n = read(fd, buffer, TAILLE_BUFFER_DERNIER_CAR)) > 0)
	{
		if(n == TAILLE_BUFFER_DERNIER_CAR || premiere_fois == 0)
		{
			strcpy(chaine_finale,buffer);
			chaine_finale[n] = '\0';
			premiere_fois = 1;
		}
		else
		{
			buffer[n] = '\0';
			for(i = 0 ; (i + n) < TAILLE_BUFFER_DERNIER_CAR ; i++)
				chaine_finale[i] = chaine_finale[i+n];
			for(i = 0 ; i < n ; i++)
				chaine_finale[TAILLE_BUFFER_DERNIER_CAR - n + i] = buffer[i];
		}
	}
	close(fd);
	chaine_finale[TAILLE_BUFFER_DERNIER_CAR] = '\0';
	printf("Les %d derniers caractères de %s : %s\n",
			TAILLE_BUFFER_DERNIER_CAR,
			nom_du_fichier,
			chaine_finale);
}
void print_derniers_car_simple(char * nom_du_fichier)
{
	int fd, n, i,k;
	char buffer[1];
	char chaine_finale[TAILLE_BUFFER_DERNIER_CAR + 1];
	if((fd = open(nom_du_fichier, O_RDONLY)) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < TAILLE_BUFFER_DERNIER_CAR +1 ; i++)
		chaine_finale[i] = '\0';
	i = 0;
	while(( n = read(fd, buffer, 1)) > 0)
	{
		if(i >= TAILLE_BUFFER_DERNIER_CAR)
		{
			for(k = 0 ; k < TAILLE_BUFFER_DERNIER_CAR ; k++)
				chaine_finale[k] = chaine_finale[k+1];
			chaine_finale[k] = buffer[0];
		}
		else
			i++;	
	}
	close(fd);
	chaine_finale[TAILLE_BUFFER_DERNIER_CAR] = '\0';
	printf("Les %d derniers caractères de %s : %s\n",
			TAILLE_BUFFER_DERNIER_CAR,
			nom_du_fichier,
			chaine_finale);
}
void mon_toupper(char * nom_du_fichier)
{
	int fd;
	char c[1];
	if((fd = open(nom_du_fichier, O_RDWR)) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	lseek(fd, 0, SEEK_SET);
	while((read(fd, c, 1)))
	{
		lseek(fd, -1 , SEEK_CUR);
		c[0] = toupper(c[0]);
		write(fd, c, 1);
	}
	close(fd);
	printf("FINI\n");
}
void mon_tolower(char * nom_du_fichier)
{
	int fd;
	char c[1];
	if((fd = open(nom_du_fichier, O_RDWR)) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	lseek(fd, 0, SEEK_SET);
	while((read(fd, c, 1)))
	{
		lseek(fd, -1 , SEEK_CUR);
		c[0] = tolower(c[0]);
		write(fd, c, 1);
	}
	close(fd);
	printf("FINI\n");
}
