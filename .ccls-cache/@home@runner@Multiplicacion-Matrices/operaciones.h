#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__
#include <stdlib.h>
struct datosMM {
  int N; /*Dimension de la matriz*/
  int H; /*Cantidad de hilos de ejecucion*/
  double *mA;
  double *mB;
  double *mC;
};

void inicializarMatrices(int n, double *mA, double *mB, double *mC);

void imprimirMatriz(int n, double *m);

void *multiplicacionMatriz(void *arg);

#endif