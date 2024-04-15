/*Definición de la lógica de las funciones presentes en matrix_operations.h*/

#include "operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Prototipos de las funciones.
void inicializarMatrices(int n, double *mA, double *mB, double *mC) {
  // Inicializa las matrices.
  for (int i = 0; i < n * n; i++) {
    mA[i] = i * 1.1;
    mB[i] = i * 2.2;
    mC[i] = i;
  }
}
void imprimirMatriz(int n, double *m) {
  // Imprime una matriz.
  if (n < 9) {
    for (int i = 0; i < n * n; i++) {
      if (i % n == 0) {
        printf("\n");
      }
      printf("%f ", m[i]);
    }
    printf("\n***************************************\n");
  } else {
    printf("\n***************************************\n");
  }
}

void *multiplicacionMatriz(void *arg) {
  struct datosMM *valorInterno = (struct datosMM *)arg;

  /* Algoritmo simple para la multiplicación de matrices */
  for (int i = 0; i < valorInterno->N; i++) {
    for (int j = 0; j < valorInterno->N; j++) {
      double *pA = valorInterno->mA + (i * valorInterno->N);
      double *pB = valorInterno->mB + j;
      double sumaTemp = 0.0; // Inicialización de sumaTemp
      for (int k = 0; k < valorInterno->N; k++, pA++, pB += valorInterno->N) {
        sumaTemp += (*pA) * (*pB);
      }
      valorInterno->mC[i * valorInterno->N + j] = sumaTemp;
    }
  }
  imprimirMatriz(valorInterno->N, valorInterno->mC);
  return NULL;
}
