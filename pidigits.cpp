/*  Este programa está basado en el algoritmo BBP para encontrar digitos

individuales de pi debido a David H.Bailey, Peter Borwein y Simonn

Plouffe, y en el programa implementado por Bailey */


#include <stdio.h>
#include <math.h>

#define NHX 16 
#define ntp 25


double expmod (double, double);
double serie (int m, int n);
void enhexa (double x, int m, char c[]);


main() {
  double pid, s1, s2, s3, s4;
  int ic = 1, sa = 1; /*  ic es la posición donde se busca el digito*/

  char chx[NHX];

while(sa!=0)
  {
           printf("Digite la posicion del digito que desea\n");
           scanf("%i", &ic);

           s1 = serie (1, ic - 1);
           s2 = serie (4, ic - 1);
           s3 = serie (5, ic - 1);
           s4 = serie (6, ic - 1);

           pid = 4. * s1 - 2. * s2 - s3 - s4;
           pid = pid - (int) pid + 1.;
           enhexa (pid, NHX, chx);

           printf (" Posicion inicial = %i\n Digitos en hexagesimal =  %10.10s\n", ic, chx);
           printf("Digite 0 para salir, o 1 para continuar\n");
           scanf("%i", &sa);
  }
}

void enhexa (double x, int nhx, char chx[])

/*  retorna, en chx, los primeros nhx digitos hexagecimales
de la fraccion de x. */

{
  int i;
  double y;
  char hx[] = "0123456789ABCDEF";

  y = fabs (x);

  for (i = 0; i < nhx; i++){
    y = 16. * (y - floor (y));
    chx[i] = hx[(int) y];
  }
}

double serie (int m, int ic)

/*  esta rutina evalua la serie  sum_k 16^(ic-k)/(8*k+m)
    usando la tecnica de exponenciación modular. */

{
  int k;
  double ak, eps, p, s, t;
  double expmod (double x, double y);
#define eps 1e-17

  s = 0.;

/*  suma la serie hasta ic */

  for (k = 0; k < ic; k++){
    ak = 8 * k + m;
    p = ic - k;
    t = expmod (p, ak);
    s = s + t / ak;
    s = s - (int) s;
  }

/*  computa algunos terminos con k >= ic. */

  for (k = ic; k <= ic + 100; k++){
    ak = 8 * k + m;
    t = pow (16., (double) (ic - k)) / ak;
    if (t < eps) break;
    s = s + t;
    s = s - (int) s;
  }
  return s;
}

double expmod (double p, double ak)

/*  expmod = 16^p mod ak.  Esta rutina usa el esquema de exponenciación
 binaria de izquierda a derecha. Vale
para  ak <= 2^24. */

{
  int i, j;
  double p1, pt, r;
  static double tp[ntp];
  static int tp1 = 0;

/*  Si esta es la primera invocacion de expm, llena la tabla tp de
potencias de 2*/

  if (tp1 == 0) {
    tp1 = 1;
    tp[0] = 1.;

    for (i = 1; i < ntp; i++) tp[i] = 2. * tp[i-1];
  }

  if (ak == 1.) return 0.;

/*  encuentra la mayor potencia de dos menor o igual a p.*/

  for (i = 0; i < ntp; i++) if (tp[i] > p) break;

  pt = tp[i-1];
  p1 = p;
  r = 1.;

/*  realiza el algoritmo de exponenciación binaria modulo ak. */

  for (j = 1; j <= i; j++){
    if (p1 >= pt){
      r = 16. * r;
      r = r - (int) (r / ak) * ak;
      p1 = p1 - pt;
    }
    pt = 0.5 * pt;
    if (pt >= 1.){
      r = r * r;
      r = r - (int) (r / ak) * ak;
    }
  }

  return r;
}
