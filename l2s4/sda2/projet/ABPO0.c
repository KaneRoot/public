#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"
#include "ABPO0.h"


bool po(Abp a)
{
	if(n(a) <= 0) return VRAI;
	int i;
	bool b = VRAI;
	for(i = 0 ; (i < n(a)) && b ; i++)
		if(v(a,i) < v(a,imont(i)))
			b = FAUX;

	return b;
}
Nat imont(Nat x)
{
	if(x==0) return 0;
	return ((x%2)==0) ? (int) (x-1)/2 : (int) x/2;
}
Abp mont(Abp a, Nat x)
{
	while(v(a,x) < v(a,imont(x)))
	{
		a = ech(a,imont(x),x);
		x = imont(x);
	}
	return a;
}
Abp ipo(Abp a, Rat s)
{
	a = inser(a,s);
	return mont(a,n(a)-1);
}
