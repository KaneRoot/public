#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"

#define V_ERROR -13.37

Abp lambda(void)
{
	Abp a = malloc(sizeof(Abp));
	a->length = 0;
	return a;
}
Abp inser(Abp a, Rat s)
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
	return (x >= n(a) || y >= n(a)) ? a : r(r(a,x,v(a,y)),y,v(a,x));
}
Nat nf(Abp a)
{
	int arrondi = (int) n(a)/2; // si n(a)/2  impair, réduction à l'entier inférieur
	return (Nat) n(a) - arrondi;
}
Rat v(Abp a, Nat x)
{
	if(x >= n(a))
		return V_ERROR;
	return a->t[x];
}
Nat n(Abp a)
{
	if(a == NULL) return -1; // Sécurité contre les segfaults.
	return a->length;
}
