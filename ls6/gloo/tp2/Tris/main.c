#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tris.h"


void Recopie(int *A, int * B, int n)
{
  int i;
  for(i=0; i<n; i++) B[i] = A[i];
}


int main()
{
  int * A, *B, i;
  int taille = 5;
  

  A = malloc(taille*sizeof(int));
  B = malloc(taille*sizeof(int));

  A[0] = 1;
  A[1] = 5;
  A[2] = 2;
  A[3] = 3;
  A[4] = 4;


  Recopie(A, B, taille);
  TriFusion(B, 0, taille-1);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");


  Recopie(A, B, taille);
  TriMax(B, taille);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");
  

  Recopie(A, B, taille);
  TriElim(B, taille);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");
	
  Recopie(A, B, taille);
  TrierTas(B, taille);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");

  Recopie(A, B, taille);
  BinInsertion(B, 0, taille-1);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");
  
  Recopie(A, B, taille);
  TriRapide(B, 0, taille-1);
  for(i=0; i<taille; i++) fprintf(stderr, "%d ", B[i]);
  fprintf(stderr,"\n");
	

  return 0;
}
