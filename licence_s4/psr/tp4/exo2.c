#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define TAILLE_MIN 1

int t[MAX];
int temp[MAX];

typedef struct
{
	int deb;
	int fin;
} data_s;

void fusion(int debut, int fin) 
{
	int i1,i2,i,mil;
	mil = (debut + fin)/2;
	i1 = debut;
	i2 = mil+1;
	i = debut;
	while((i1<=mil) && (i2<=fin)) 
	{
		if(t[i1]<t[i2])
		{
			temp[i] = t[i1]; 
			i++; 
			i1++;
		}
		else
		{
			temp[i] = t[i2]; 
			i++; 
			i2++;
		}
	}
	while(i1<=mil) 
	{
		temp[i] = t[i1]; 
		i++; 
		i1++;
	}
	while(i2<=fin) 
	{
		temp[i] = t[i2]; 
		i++; 
		i2++;
	}
	for(i=debut;i<=fin;i++)
		t[i] = temp[i];
}

void * faire_fusion(void * arg)
{
	data_s * d = (data_s*) arg;
	int debut = d->deb;
	int fin = d->fin;
	printf("Debut %d :: Fin %d fin-debut %d \n", debut, fin, (fin - debut));
	if((fin - debut) < TAILLE_MIN)
	{
		pthread_exit(NULL);
	}
	else
	{
		printf("Else \n");
		pthread_t t1,t2;
		data_s d1 = { .deb = debut, .fin = (debut + fin)/2 };
		data_s d2 = { .deb = (debut + fin)/2 +1 , .fin = fin};
		
		if(pthread_create(&t1, NULL, faire_fusion, (void*) &d1) != 0)
			printf("Erreur\n");
		if(pthread_create(&t2, NULL, faire_fusion, (void*) &d2) != 0)
			printf("Erreur\n");

		pthread_join(t1,NULL);
		pthread_join(t2,NULL);

		fusion(debut,fin);
		pthread_exit(NULL);

	}
	return NULL;
}

int main(int argc, char * argv[])
{
	int i;
	data_s d;
	d.deb = 0;
	d.fin = MAX-1;
	srand (time (NULL));
	// On rempli les tableaux
	
	for(i = 0; i < MAX ; i++)
		t[i] = ((rand() % 3) +i + 1)*(rand() %4 +1) ;

	// Affichage du tableau
	for(i = 0 ; i < MAX ; i++)
		printf("t[%d] : %d\n",i, t[i]);

	pthread_t t1;

	if(pthread_create(&t1, NULL, faire_fusion, (void*) &d) != 0)
		printf("Erreur\n");

	pthread_join(t1,NULL);
	// Affichage du tableau
	for(i = 0 ; i < MAX ; i++)
		printf("t[%d] : %d\n",i, t[i]);

	return EXIT_SUCCESS;
}

