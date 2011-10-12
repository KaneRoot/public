#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;

uint32 make_uint32(unsigned char o0, unsigned char o1, unsigned char o2, unsigned char o3)
{
	union 
	{ 
		uint32 i;
		unsigned char o[4];
	} v;
	v.o[0] = o0;
	v.o[1] = o1;
	v.o[2] = o2;
	v.o[3] = o3;
	return v.i;
}

/* retourne le n-ième ( de 0 à 31 ) bit d'un float */
int nieme_bit(float f, int n)
{
	union
	{
		uint32 i;
		float f;
	} v;
	v.f = f;
	return (v.i >> n) & 0x1;
}

void decortiquer_float(float f)
{
	int i;
	printf("%f : ",f);
	for(i = 31 ; i >= 0 ; i--) printf("%d", nieme_bit(f,i));
	printf("\n");
	for(i = 31 ; i >= 0 ; i--) 
	{
		if( i == 31 )
		{
			printf("bit de signe : %d \n", nieme_bit(f,i));
		}
		else if(i <= 30 && i > 22 )
		{
			if(i == 30) printf("Exposant : ");
			printf("%d",nieme_bit(f,i));
			if(i == 23) printf("\n");
		}
		else
		{
			if(i == 22) printf("Mantisse : ");
			printf("%d", nieme_bit(f,i));
		}
	}
	printf("\n");
}

int main(int argc, char * argv[])
{
	/*	Little-Big endian	*/
	uint32 k;
	k = make_uint32(1,0,0,0);
	printf("make_uint32(1,0,0,0) : %d\n",k);

	k = make_uint32(0,0,0,1);
	printf("make_uint32(0,0,0,1) : %d\n",k);

	decortiquer_float(10.5);
	decortiquer_float(-10.5);
	decortiquer_float(0.536);
	decortiquer_float(-0.566613);

	return EXIT_SUCCESS;
}
