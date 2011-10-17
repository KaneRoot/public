#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * is this the stupidest code all over the world ?
 * or any student first system call code ?
 *
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		// if the fucking user doesn't give a signal code on args, then kill -9 program
		raise(9);
		return EXIT_SUCCESS;
	}
	// else apply user arg as signal sent to the program
	if (raise(atoi(argv[1])) == -1 )
		perror(NULL);
	return EXIT_SUCCESS;
}
