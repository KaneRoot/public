#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SAMPLES_PER_PERIOD 1000

FILE *fp;
float pi = M_PI;

void
coef_sf (int nb_harm, float a[], float b[])
{
  int i = 0;

  for (i = 1; i <= nb_harm; i++)
    a[i] = (1 / (pi * i)) * (1 - cos(pi * i));	// à modifier (fait)

  for (i = 1; i <= nb_harm; i++)
    b[i] = (1 / (pi * i)) * sin (pi * i);	// à modifier (fait)

  return;
}

float
somcos (int nb_harm, float f, float x, float bb[])
{
  int i = 0;
  float sc = 0.0;

  for (i = 1; i <= nb_harm; i++)
  {
    sc += bb[i] * cos (2 * pi * (float) i * f * x);
  }

  return sc;
}

float
somsin (int nb_harm, float f, float x, float aa[])
{
  int i = 0;
  float ss = 0.0;

  for (i = 1; i <= nb_harm; i++)
  {
    ss += aa[i] * sin (2 * pi * (float) i * f * x);
  }

  return ss;
}

int
main ()
{
  int i, nb_harm, nb_periodes;
  float periode, fondamentale, t, dt, *aa, *bb, sa, sb, ss;

  printf (" Nb harmoniques = ");
  scanf ("%d", &nb_harm);

  aa = (float *) malloc ((unsigned) (nb_harm + 1) * sizeof (float));
  bb = (float *) malloc ((unsigned) (nb_harm + 1) * sizeof (float));

  coef_sf (nb_harm, aa, bb);

  for (i = 0; i <= nb_harm; i++)
  {
    printf (" a[%d] = %8.4f ; b[%d] = %8.4f \n", i, aa[i], i, bb[i]);
  }

  printf (" Periode = ");
  scanf ("%f", &periode);

  fondamentale = 1. / periode;

  printf (" Nb periodes = ");
  scanf ("%d", &nb_periodes);

  dt = periode / (float) (SAMPLES_PER_PERIOD);
  t = -3.;

  fp = fopen ("sf.dat", "w");

  while (t < (nb_periodes * periode))
  {
    sa = somcos (nb_harm, fondamentale, t, bb);
    sb = somsin (nb_harm, fondamentale, t, aa);
    ss = sa + sb + dt;							// à modifier (fait)

    fprintf (fp, "%f %f\n", t, ss);
    t += dt;
  }

  fclose (fp);
  printf (" Nb harmoniques = %d\n", nb_harm);
  printf ("Sortie dans sf.dat\n");

  return 0;
}
