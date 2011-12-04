#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"
#include "ABPO0.h"
#include "ABPO1.h"

Nat imin(Abp a, Nat x)
{
	if((n(a)-1) < ((2*x)+2))
	{
		if((n(a)-1) < 2*x+1)	
			return x;
		else					
			return (2*x)+1;
	}
	return (v(a,(2*x)+1) < v(a,(2*x)+2)) ? (2*x)+1 : (2*x)+2;
}

Abp desc(Abp a, Nat x)
{
	while(v(a,x) > v(a,imin(a,x)))
	{
		ech(a,x,imin(a,x));
		x = imin(a,x);
	}
	return a;
}
Abp spo(Abp a, Nat x)
{
	if(x >= n(a)) return a;
	a = ech(a,x,n(a)-1);
	s(a);
	return desc(a,x);
}
