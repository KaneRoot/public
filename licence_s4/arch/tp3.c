#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void table_de_verite(int a, int b, int c)
{
	int i,j,k;
	printf("a . b . c : a=%d,b=%d,c=%d\n",a,b,c);
	// table de vérité &
	for(i = 0; i < 2 ; i++)
	{
		for(j = 0; j < 2 ; j++)
		{
			for(k = 0 ; k < 2 ; k++)
			{
				printf("%d %d %d = %d\n", a, b , c, a&b&c);
				c = (c + 1)%2;
			}
			b = (b + 1)%2;
		}
		a = (a + 1)%2;
	}
}

int main(int argc, char * argv[])
{
	int a = 1 , b = 1;
	printf("%d : 1 & 1 \n", a & b);
	table_de_verite(0,0,0);
	return EXIT_SUCCESS;
}

