
int Pere(int i)
{
  return ((i+1)/2-1);
}


int Gauche(int i)
{
  return (2*i+1);
}
    

int Droit(int i)
{
  return (2*i+2);
}


void Entasser(int * A, int i, int nelements)
{
  int g, d, max, tmp;

  g = Gauche(i);
  d = Droit(i);
  max = i;
  
  if ((g < nelements) &&  (A[g] > A[max])) max = g;
  if ((d < nelements) &&  (A[d] > A[max])) max = d;
  if (max != i) 
    {
      tmp = A[i];
      A[i] = A[max];
      A[max] = tmp;
      Entasser(A, max, nelements);
    }
}


void ConstruireTas(int * A, int size)
{
  int i;
  for(i = size/2-1; i >=0; i--) Entasser(A, i, size);
}



void TrierTas(int * A, int size)
{
  int tmp, i, nelements = size;

  ConstruireTas(A, size);
  for(i = size-1; i >= 1; i--)
    {
      tmp = A[0];
      A[0] = A[i];
      A[i] = tmp;
      nelements = nelements -1;
      Entasser(A, 0, nelements);
    }
}



