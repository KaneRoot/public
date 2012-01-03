#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INCONNU -1

int t[MAX];

void * faire_fibo(void * arg)
{
	int * n = (int *) arg;
	int * n_1;
	int * n_2;
	int * retour;
	if(*n < 2)
	{
		pthread_exit(n);
	}
	else
	{
		pthread_t t1,t2;
		void *r1;
		void *r2;
		n_1 = malloc(sizeof(int));
		n_2 = malloc(sizeof(int));

		*n_1 = *n-1;
		*n_2 = *n-2;
		
		if(pthread_create(&t1, NULL, faire_fibo, (void*) n_1) != 0)
			printf("Erreur\n");
		if(pthread_create(&t2, NULL, faire_fibo, (void*) n_2) != 0)
			printf("Erreur\n");

		pthread_join(t1,&r1);
		pthread_join(t2,&r2);

		retour = malloc(sizeof(int));
		*retour = *((int*)r1) + *((int*)r2);
		free(r1);
		free(r2);

		pthread_exit(retour);

	}
	return NULL;
}
void fibo_1(int * n)
{
	void * retour;
	pthread_t t0;

	if(pthread_create(&t0, NULL, faire_fibo, (void*) n) != 0)
		printf("Erreur\n");

	pthread_join(t0,&retour);
	printf("retour : %d\n", *((int*)retour));
	free(retour);
}
void * faire_fibo2(void * arg)
{
	int * n = (int *) arg;
	if(*n < 2)
	{
		t[*n] = 1;
		pthread_exit(NULL);
	}
	else
	{
		pthread_t t1,t2;
		int * n_1 = malloc(sizeof(int));
		int * n_2 = malloc(sizeof(int));
		*n_1 = *n - 1;
		*n_2 = *n - 2;
		
		if(pthread_create(&t1, NULL, faire_fibo2, (void*) n_1) != 0)
			printf("Erreur\n");
		if(pthread_create(&t2, NULL, faire_fibo2, (void*) n_2) != 0)
			printf("Erreur\n");

		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
		free(n_1);
		free(n_2);

		t[*n] = t[*n - 1] + t[*n - 2];

		pthread_exit(NULL);
	}
	return NULL;
}
void fibo_2(int * n)
{
	void * retour;
	pthread_t t0;

	if(pthread_create(&t0, NULL, faire_fibo2, (void*) n) != 0)
		printf("Erreur\n");

	pthread_join(t0,NULL);
	printf("retour : %d\n", *(t + *((int*)n)));
	free(retour);
}
int main(int argc, char * argv[])
{
	int i;
	for(i = 0; i < MAX ; i++)
		t[i] = INCONNU;
	int * nb_recherche = malloc(sizeof(int));
	if(*nb_recherche == 0)
		*nb_recherche = atoi(argv[1]);

	fibo_1(nb_recherche);
	fibo_2(nb_recherche);
	for(i = 0 ; i <= *nb_recherche ; i++)
		printf("Tableau : t[%d] = %d\n",i,t[i]);

	return EXIT_SUCCESS;
}

