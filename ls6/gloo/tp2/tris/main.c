#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tris.h"

#define FAUX 0
#define VRAI 1

void Recopie(int *A, int * B, int n)
{
	int i;
	for(i=0; i<n; i++) B[i] = A[i];
}

int est_valide(int * x, int taille)
{
	while(--taille > 0)
		if( x[taille] < x[taille - 1] )
			return FAUX;

	return VRAI;
}
void afficher_validite(int *x, int taille)
{
	int i ;
	if(VRAI == est_valide(x,taille))
		printf("\033[32mCet algo est valide : \033[00m\t\t");
	else
		printf("\033[31mCet algo n'est pas valide : \033[00m\t");
	for( i = 0 ; i < taille ; i++)
		printf(" %d ", x[i]);
	printf("\n");
}
void algo_test()
{
}

int main()
{
	int * A, *B, i;
	int taille = 10;


	A = malloc(taille*sizeof(int));
	B = malloc(taille*sizeof(int));

	for( i = 0 ; i < taille ; i++)
		A[i] = (i % 3) * (taille - i) * -1;


	Recopie(A, B, taille);
	TriFusion(B, 0, taille-1);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");


	Recopie(A, B, taille);
	TriMax(B, taille);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");


	Recopie(A, B, taille);
	TriElim(B, taille);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");

	Recopie(A, B, taille);
	TrierTas(B, taille);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");

	Recopie(A, B, taille);
	BinInsertion(B, 0, taille-1);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");

	Recopie(A, B, taille);
	TriRapide(B, 0, taille-1);
	afficher_validite(B,taille);
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");


	return 0;
}
