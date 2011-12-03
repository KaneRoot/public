#ifndef __ABP_H_
#define __ABP_H_

#define N 10

typedef struct {
	Rel t[N];
	Nat length;
} *Abp;

Abp lambda(void);	// ^
Abp i(Abp, Rel);
Abp s(Abp);
Abp r(Abp,Nat,Rel);
Abp ech(Abp,Nat,Nat);
Nat n(Abp);
Nat nf(Abp);
Rel v(Abp,Nat);

#endif

