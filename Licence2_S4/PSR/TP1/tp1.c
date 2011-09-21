#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF1 10

int main(int argc, char * argv[])
{
	//printf("EOF : %d\n",EOF);
	char c = (char) getchar();
	printf("%c\n",c);
	return EXIT_SUCCESS;
}
int getchar1(void)
{
	char c;
	read(0, &c, 1);
	return (int) c;
}
int getchar2(void)
{
	return 0;
}
