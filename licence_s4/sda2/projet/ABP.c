#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"

Abp lambda(void)
{
	Abp a = malloc(sizeof(Abp));
	a->length = 0;
	return a;
}
Abp i(Abp a, Rat s)
{
	if(a == NULL) a = lambda();
	a->t[n(a)] = s;
	a->length++;
	return a;
}
Abp s(Abp a)
{
	if(a != NULL && a->length > 0)
		a->length--;
	return a;
}

Abp r(Abp a, Nat x, Rat s)
{
	if(x >= n(a))
		return a;
	a->t[x] = s;
	return a;
}
Abp ech(Abp a, Nat x, Nat y)
{
}
Nat nf(Abp a)
{
	// n(i(a,s)) - arrondi(n(i(a,s))/2)
	int arrondi = (int) n(a)/2;
	return (Nat) n(a) - arrondi;
}
Rat v(Abp,Nat);
Nat n(Abp a)
{
	if(a == NULL) return 0; // Sécurité contre les segfaults.
	return a->length;
}
