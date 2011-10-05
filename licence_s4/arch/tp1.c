#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_OCTETS 8

int d2c(int n)
{
	if( 0 <= n && n < 10)
		return '0' + n;
	else if(n < 36)
		return 'A' + (n - 10);
	else
		return '?';
}
int val_max_int()
{
	int n = 0,entier = 1;
	while(entier != 0 )
	{
		if(entier > 0) n++;
		entier *= 2;
	}
	return n ;
}
int val_max_uint()
{
	int n = 0;
	unsigned int entier = 1;
	while(entier != 0)
	{
		if(entier > 0) n++;
		entier *= 2;
	}
	return n;
}
char * changement_de_base(int nb, int base)
{
	int i = 0;
	char * c = malloc(sizeof(char) * NB_OCTETS + 1);
	for(i = 0 ; i < NB_OCTETS ; i++)
	{
		c[NB_OCTETS - 1 - i] = d2c(nb%base);
		nb = nb/base;
	}
	c[NB_OCTETS] = '\0';
	return c;
}

int main(int argc, char * argv[])
{
	printf("changement_de_base(8,8) : %s \n", changement_de_base(8,8));
	printf("changement_de_base(192,2) : %s \n", changement_de_base(192,2));
	printf("changement_de_base(192,8) : %s \n", changement_de_base(192,8));
	printf("changement_de_base(192,16) : %s \n", changement_de_base(192,16));
	printf("changement_de_base(192,28) : %s \n", changement_de_base(192,28));
	printf("d2c(5) : %c\n", d2c(5));
	printf("val_max_int() : %d\n", val_max_int());
	printf("val_max_uint() : %d\n", val_max_uint());
	//printf("entier signé : %ld non signé : %ld\n", sizeof(int), sizeof(unsigned int));
	return EXIT_SUCCESS;
}
