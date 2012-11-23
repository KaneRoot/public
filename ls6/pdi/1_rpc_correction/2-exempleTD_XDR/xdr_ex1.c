#include <stdio.h>
#include <stdlib.h>
#include <rpc/types.h>
#include <rpc/xdr.h>

#define LIRE 0
#define ECRIRE 1
#define TAILLE 16
#define LONGCHAINE 20

int main (int argc, char *argv[])
{
  XDR xdr_encode, xdr_decode ;
  char tab[TAILLE] ;
  
  int entier = -1001 ; // 4 octets
  float reel = 3.14 ; // 4 octets
  
  char *chaine0 = "Bingo !" ; // 7 caracteres
  char *chaine1 = "Re Bingo !" ; // 10 caracteres
  
  char *ptr0 = NULL ;
  char *ptr1 = NULL ;

  /* Creation des flots XDR, c.a.d. "suites de donnees accessibles en 
     lecture ou ecriture (comparables en cela a la structure FILE). 
     Une telle suite de donnees supporte d'etre ecrite puis lue sur des 
     plate-formes differentes". La structure XDR representant le flot 
     dispose  notamment : d'un tampon, d'un curseur, du parametre 
     permettant de choisir entre encodage OU decodage */
  xdrmem_create(&xdr_encode, tab, TAILLE, XDR_ENCODE) ;
  xdrmem_create(&xdr_decode, tab, TAILLE, XDR_DECODE) ;

  /* Encodage dans un flot XDR ------------ */
  if (!xdr_int(&xdr_encode, &entier))
    fprintf(stdout,"Erreur d'encodage de l'entier\n") ;
  if (!xdr_float(&xdr_encode, &reel))
    fprintf(stdout,"Erreur d'encodage du reel\n") ;

  if (!xdr_string(&xdr_encode, &chaine0, LONGCHAINE))
    fprintf(stdout,"Erreur d'encodage de la chaine 0\n") ;
  if (!xdr_string(&xdr_encode, &chaine1, LONGCHAINE))
    fprintf(stdout,"Erreur d'encodage de la chaine 1\n") ;

  /* Decodage du flot XDR ------------ */
  entier = 0 ;
  reel = 0 ;
  
  if (!xdr_int(&xdr_decode, &entier))
    fprintf(stdout,"Erreur de decodage de l'entier\n") ;
  else
    fprintf(stdout,"Entier lu : %d\n",entier) ;
  if (!xdr_float(&xdr_decode, &reel))
    fprintf(stdout,"Erreur de decodage du reel\n") ;
  else
    fprintf(stdout,"Reel lu : %f\n",reel) ;

  ptr1 = malloc(LONGCHAINE * sizeof(char)) ;
  fprintf(stdout,"les pointeurs sur les chaines : %x %x\n",ptr0,ptr1) ;
  if (!xdr_string(&xdr_decode, &ptr0, LONGCHAINE))
    fprintf(stdout,"Erreur decodage chaine 0\n") ;
  else
    fprintf(stdout,"Chaine lue : %s\n",ptr0) ;
  if (!xdr_string(&xdr_decode, &ptr1, LONGCHAINE))
    fprintf(stdout,"Erreur decodage chaine 1\n") ;
  else
    fprintf(stdout,"Chaine lue : %s\n",ptr1) ;

  fprintf(stdout,"les pointeurs sur les chaines : %x %x\n",ptr0,ptr1) ;

  xdr_free((xdrproc_t)xdr_string, (char*)&ptr0) ; // libère ce qui a été alloué
  xdr_free((xdrproc_t)xdr_string, (char*)&ptr1) ; // dans xdr_string (et met à NULL)
  
  free(ptr0) ; // Libère le pointeur alloué
  free(ptr1) ; // aucun effet car déjà à NULL
  
  xdr_destroy(&xdr_encode) ; // détruit le flot XDR
  xdr_destroy(&xdr_decode) ;

  return(0) ; 
}


/*

-------------------------------------------
Affichage a l'execution (#define TAILLE 256)
-------------------------------------------
Entier lu : -1001
Reel lu : 3.140000
les pointeurs sur les chaines : 0 8049bd8
Chaine lue : Bingo !
Chaine lue : Re Bingo !
les pointeurs sur les chaines : 8049bf0 8049bd8


-------------------------------------------
Affichage a l'execution (#define TAILLE 16)
-------------------------------------------
Erreur d'encodage de la chaine 0
Erreur d'encodage de la chaine 1
Entier lu : -1001
Reel lu : 3.140000
les pointeurs sur les chaines : 0 8049b70
Erreur decodage chaine 0
Erreur decodage chaine 1
les pointeurs sur les chaines : 8049b88 8049b70

*/
