#ifndef __ABP_H_
#define __ABP_H_

#define N 10

typedef struct {
	Rat t[N];
	Nat length;
} *Abp;

Abp lambda(void);	// ^
Abp i(Abp, Rat);
Abp s(Abp);
Abp r(Abp,Nat,Rat);
Abp ech(Abp,Nat,Nat);
Nat n(Abp);
Nat nf(Abp);
Rat v(Abp,Nat);

#endif

