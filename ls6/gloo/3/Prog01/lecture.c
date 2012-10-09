#include <stdio.h>



int main()
{
  FILE * f = fopen("fichiersource","r");
  char prenom[9], nom[8], classe[8];

  fscanf(f,"%s\n%s\n%s\n\n",prenom,nom,classe);
  fprintf(stderr,"%s\n%s\n%s\n\n",prenom,nom,classe);
  fscanf(f,"%s\n%s\n%s\n\n",prenom,nom,classe);
  fprintf(stderr,"%s\n%s\n%s\n\n",prenom,nom,classe);
  fscanf(f,"%s\n%s\n%s\n\n",prenom,nom,classe);
  fprintf(stderr,"%s\n%s\n%s\n\n",prenom,nom,classe);

  return 0;
}
