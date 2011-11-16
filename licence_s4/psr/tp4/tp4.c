#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P 1
#define Q 3
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int buffer[1];

void * cons(void * arg)
{
	int i = Q * 10;
	while(i != 0)
	{
		pthread_mutex_lock(&mut);
		printf("buffer[0] = %d\n", buffer[0]);
		pthread_mutex_unlock(&mut);
		i--;
	}
	pthread_exit(NULL);
}
void * prod(void * arg)
{
	int i = P * 10;
	srand (time (NULL));
	while(i != 0)
	{
		pthread_mutex_lock(&mut);
		buffer[0] = rand() % 100;
		pthread_mutex_unlock(&mut);
		i--;
	}
	pthread_exit(NULL);
}
int main(int argc, char * argv[])
{
	int i;
	pthread_t p[P]; // Producteurs
	pthread_t q[Q];	// Consommateurs
	
	for(i = 0 ; i < P ; i++)
		if(pthread_create(&p[i], NULL, prod, NULL) != 0)
			printf("Erreur\n");

	for(i = 0 ; i < Q ; i++)
		if(pthread_create(&q[i], NULL, cons, NULL) != 0)
			printf("Erreur\n");

	for(i = 0; i < P ; i++)
		pthread_join(p[i], NULL);

	for(i = 0; i < Q ; i++)
		pthread_join(q[i], NULL);

	return EXIT_SUCCESS;
}

