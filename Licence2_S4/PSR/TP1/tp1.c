#include "tp1.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

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
	int e;
	struct stat stat_buf;
	if((stat(argv[1],&stat_buf)) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	switch(stat_buf.st_mode)
	{
		case S_ISREG :
			printf("Ce fichier est ordinaire\n");
		break;
		default :
			printf("RIEN A DIRE \n");
		break;
	}

}
