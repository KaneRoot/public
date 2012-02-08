#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * ma_nouvelle_sequence_control (void * arg)
{
	int i;
	for (i = 0 ; i < 10 ; i++) {
		printf ("%s: %d\n", (char*)arg, i);
		sleep (1);
	}
	pthread_exit (0);
}

int main(int argc, char * argv[])
{
	pthread_t t0,t1,t2;

	pthread_create(&t0,NULL,ma_nouvelle_sequence_control, "Thread 1" );
	pthread_create(&t1,NULL,ma_nouvelle_sequence_control, "Thread 2" );
	pthread_create(&t2,NULL,ma_nouvelle_sequence_control, "Thread 3" );

	pthread_join(t0,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	return EXIT_SUCCESS;
}

