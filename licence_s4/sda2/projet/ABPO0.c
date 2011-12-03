#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"
#include "ABPO0.h"


bool po(Abp a)
{
	if(n(a) <= 0) return VRAI;
	//return v(a,n(a)-1) >= v(inser(a,s),mount(a,n(a
	int i;
	bool b = VRAI;
	for(i = 0 ; i < n(a) && b ; i++)
		if(v(a,i) < v(a,mont(a,i)))
			b = FAUX;

	return b;
}
Nat mont(Abp a, Nat x)
{
	if(x==0) return 0;
	return ((x%2)==0) ? (int) (x-1)/2 : (int) x/2;
}
Abp ipo(Abp a, Rat s)
{
	if(n(a) <= 0) return inser(a,s);
	if(s < v(a,mont(a,n(a))))
	{
		a = inser(a,s);
		a = ech(a,mont(a,n(a)-1),n(a)-1);
	}
	else
		a = inser(a,s);
	return a;
}
