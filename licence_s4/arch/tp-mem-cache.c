#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define TAILLE1 2
#define TAILLE2 3
#define TTAB 128
#define TAILLE_LIGNE 32

int n_cache = 0;
int l_cache = 0;

void exo1()
{
	int i,j;
	int t[TAILLE1][TAILLE2];
	for(i = 0 ; i < TAILLE1 ; i++)
		for(j = 0 ; j < TAILLE2 ; j++)
			printf("Emplacement mémoire t[%d][%d] : %d\n", i, j, &t[i][j]);
}
void exo1_lignes()
{
	int i,j;
	int t[TTAB][TTAB];
	for(i = 0 ; i < TTAB ; i++)
		for(j = 0 ; j < TTAB ; j++)
			t[i][j] = 0;
}
void exo1_colonnes()
{
	int i,j;
	int t[TTAB][TTAB];
	for(j = 0 ; j < TTAB ; j++)
		for(i = 0 ; i < TTAB ; i++)
			t[i][j] = 0;
}
int puissance2(int x)
{
	int i, y = 1;
	for(i = 0 ; i < x; i++)
		y *= 2;
	return y;
}
int exo2_extract(int x, int n)
{
	return (x >> n) & 0x1;
}
void exo2_putbit1(int * x, int n)
{
	*x = *x | puissance2(n);
}
void exo2_putbit0(int * x, int n)
{
	*x = *x ^ puissance2(n);
}
void tests_exo2()
{
	printf("extract 2 1 : %d\n", exo2_extract(2,1));
	int x = 1;
	exo2_putbit1(&x, 6);
	printf("putbit1 0, 6 : %d\n", x);
	exo2_putbit0(&x, 6);
	printf("putbit0 0, 6 : %d\n", x);
	exo2_putbit1(&x, 5);
	exo2_putbit1(&x, 4);
	printf("x : %d\n", x);
	exo2_putbit0(&x, 5);
	printf("x : %d\n", x);
	exo2_putbit0(&x, 4);
	printf("x : %d\n", x);
}
int exo2_extract2(int x, int n, int t)
{
	int y = 0,i;
	for(i = 0 ; i < t ; i++)
		if(exo2_extract(x,n-i)==1)
			exo2_putbit1(&y,n-i);
	return y;
}
void tests_exo2_d()
{
	int x = 0xFF;
	int y = exo2_extract2(x, 3, 2);
	printf("x : %d\n",x);
	printf("y : %d\n",y);
}
int ** creation_cache()
{
	int i, j, **cache;
	cache = (int **) malloc(sizeof(int*) * n_cache * l_cache);
	for(i = 0 ; i < (n_cache*l_cache) ; i++)
	{
		cache[i] = malloc(TAILLE_LIGNE);
		for(j = 0 ; j < TAILLE_LIGNE ; j++)
			cache[i][j] = 0;
	}

	return cache;
}
void afficher_cache(int **cache)
{
	int i, j, k;
	for(i = 0 ; i < n_cache ; i++)
		for(j = 0 ; j < l_cache ; j++)
			for(k = 0 ; k < TAILLE_LIGNE ; k++
}
void exo3(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage %s n l \n", argv[0]);
		exit(-1);
	}
	n_cache = atoi(argv[1]);
	l_cache = atoi(argv[2]);
}

int main(int argc, char * argv[])
{
	//exo1_lignes();
	//exo1_colonnes();
	//tests_exo2();
	//tests_exo2_d();
	//exo3(argc, argv);
	return EXIT_SUCCESS;
}

