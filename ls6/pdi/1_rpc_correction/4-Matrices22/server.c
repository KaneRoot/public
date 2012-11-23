#include "include.h"

matrice22* multiplier(matrice22 * m) { 
  static matrice22 mres ;
  
  printf(" Sur le serveur matrice 1 =  : \n%f %f \n%f %f\n",(m[0]).tab[0][0], (m[0]).tab[0][1], (m[0]).tab[1][0], (m[0]).tab[1][1]) ;
  printf(" Sur le serveur matrice 2 =  : \n%f %f \n%f %f\n",(m[1]).tab[0][0], (m[1]).tab[0][1], (m[1]).tab[1][0], (m[1]).tab[1][1]) ;

  mres.tab[0][0] = (m[0]).tab[0][0] * (m[1]).tab[0][0] + (m[0]).tab[0][1] * (m[1]).tab[1][0] ;
  mres.tab[1][0] = (m[0]).tab[1][0] * (m[1]).tab[0][0] + (m[0]).tab[1][1] * (m[1]).tab[1][0] ;
  mres.tab[0][1] = (m[0]).tab[0][0] * (m[1]).tab[0][1] + (m[0]).tab[0][1] * (m[1]).tab[1][1] ;
  mres.tab[1][1] = (m[0]).tab[1][0] * (m[1]).tab[0][1] + (m[0]).tab[1][1] * (m[1]).tab[1][1] ; 

  printf(" Sur le serveur le resultat est : \n%f %f \n%f %f\n", mres.tab[0][0], mres.tab[0][1], mres.tab[1][0], mres.tab[1][1]) ;

  return &mres ;
}

matrice22* additionner(matrice22* m)
{ 
  static matrice22 mres ;
  
  printf(" Sur le serveur matrice 1 =  : \n%f %f \n%f %f\n",(m[0]).tab[0][0], (m[0]).tab[0][1],(m[0]).tab[1][0],(m[0]).tab[1][1]) ;
  printf(" Sur le serveur matrice 2 =  : \n%f %f \n%f %f\n",(m[1]).tab[0][0], (m[1]).tab[0][1],(m[1]).tab[1][0],(m[1]).tab[1][1]) ;

  mres.tab[0][0] = (m[0]).tab[0][0] + (m[1]).tab[0][0] ;
  mres.tab[1][0] = (m[0]).tab[1][0] + (m[1]).tab[1][0] ;
  mres.tab[0][1] = (m[0]).tab[0][1] + (m[1]).tab[0][1] ;
  mres.tab[1][1] = (m[0]).tab[1][1] + (m[1]).tab[1][1] ;

  printf(" Sur le serveur le resultat est : \n%f %f \n%f %f\n", mres.tab[0][0], mres.tab[0][1], mres.tab[1][0], mres.tab[1][1]) ;

  return &mres ;
}


int main (void)
{
  // on enregistre les deux procédures RPC
  registerrpc(PROGNUM,VERSNUM,1,multiplier, xdr_mat2,xdr_mat) ;
  registerrpc(PROGNUM,VERSNUM,2,additionner,xdr_mat2,xdr_mat) ;
  
  svc_run() ;
  
  return(0) ;

}

