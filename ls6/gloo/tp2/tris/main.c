#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tris.h"

#define FAUX 0
#define VRAI 1

void Recopie(int *A, int * B, int n) {
	int i;
	for(i=0; i<n; i++) B[i] = A[i];
}
int est_valide(int * x, int taille) {
	while(--taille > 0)
		if( x[taille] < x[taille - 1] )
			return FAUX;

	return VRAI;
}
void afficher_validite(int *x, int taille) {
	int i ;
	if(VRAI == est_valide(x,taille))
		printf("%20s : ", "\033[32mvalide\033[00m");
	else
		printf("%20s : ", "\033[31mnon valide\033[00m");
	for( i = 0 ; i < taille ; i++)
		printf(" %3d ", x[i]);
	printf("\n");
}
void algo_test(int *A, int *B, int taille) {
	Recopie(A, B, taille);
	TriFusion(B, 0, taille-1);
	printf("%15s : ", "tri fusion");
	afficher_validite(B,taille);

	Recopie(A, B, taille);
	TriMax(B, taille);
	printf("%15s : ", "tri max");
	afficher_validite(B,taille);

	Recopie(A, B, taille);
	TriElim(B, taille);
	printf("%15s : ", "tri elimination");
	afficher_validite(B,taille);

	Recopie(A, B, taille);
	TrierTas(B, taille);
	printf("%15s : ", "tri tas");
	afficher_validite(B,taille);

	Recopie(A, B, taille);
	BinInsertion(B, 0, taille-1);
	printf("%15s : ", "bininsertion");
	afficher_validite(B,taille);

	Recopie(A, B, taille);
	TriRapide(B, 0, taille-1);
	printf("%15s : ", "tri rapide");
	afficher_validite(B,taille);

}
int main()
{
	int * A, *B, i;
	int taille = 10;


	A = malloc(taille*sizeof(int));
	B = malloc(taille*sizeof(int));

	for( i = 0 ; i < taille ; i++)
		A[i] = (i % 3) * (taille - i) * -1;
	A[5] = 3;

	algo_test(A,B,taille);
	return 0;
}
//	for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
//	fprintf(stderr,"\n");
