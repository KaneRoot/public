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
	for(i = 0 ; i < n(a) || b ; i++)
		if(v(a,i) < mount(a,i))
			b = FAUX;

	return b;
}
//Abp ipo(Abp, Rat);
//Nat mont(Abp, Nat);
