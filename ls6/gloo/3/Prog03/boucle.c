#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXNUM 12

int main()
{
	int i,j,k,l,m,n;
	int compteur = 0;

	for(i=0; i<20;i++)
		for(j=10; j>0;j--)
			for(k=0; k<i;k++)
				for(l=10; l>j; l--)
					for(m=10; m>k; m--)
						for(n=10; n>0; n--)
							compteur++;

	return 0;
}
