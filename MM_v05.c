/**************************************************************************************
 * Fecha: 4/4/2024
 * Autor: Daniel Carvajal
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación
 *de matrices. La idea principal, es construir paso a paso la implementación
 *para hacer uso de la biblioteca PTHREAD. Se implementa el Algoritmo Clásico de
 *multiplicación de matrices, para matrices cuadradas, es decir, la dimensión de
 *filas es igual a la de columnas. A continuación se describen los paso
 * 	- Reserva de memoria
 * 		- Creación de punteros para matrices del tipo doble
 * 		- Asignación de memoria
 * 		- Ingreso de argumentos de entrada (Dimensión matriz, número de
 *hilos)
 *		- Validación argumentos de entrada
 *		- Inicializar las matrices
 *  	- Imprimir las matrices
 *  	- Función para inicializar las matrices
 *  	- Función para imprimir las matrices
 *  	- Algoritmo clásico de multiplicación matrices
 * 	- Se verifica el resultado
 *  	- Función para multiplicación las matrices
 *  	- Declaración vector de hilos
 *  	- Creación de hilos según tamaño de vector de hilos
 *  	- Crear estructura de datos que encapsule los argumentos de entrada de
 *la función MM Implementación de paralelismo: resolución de la multiplicación
 *de matrices
 * 	- Se crea el vector de hilos
 * 	- Se tiene pendiente la exclusión de los hilos
 * 	- Se pasa a globales las matrices
 * 	- Encapsular los datos para enviarlos a la función MxM
 * 	- Se desencapsulan los datos dentro de la función MxM (descomprimen)
 *************************************************************************************/

// Librerias usadas en el programa.
#include "operaciones.h"
#include <pthread.h>
#include <stdio.h>

// Reserva de memoria.
// Definicion de la palabra RESERVA para denotar el tamano del espacio de
// memoria.
#define RESERVA (1024 * 128 * 64 * 8)
// Creación de un vector cuyo tamano sera igual a RESERVA
static double MEM_CHUNK[RESERVA];

int main(int argc, char *argv[]) {
  // Comprueba si se han proporcionado suficientes argumentos.
  if (argc < 3) {
    printf("No se han ingresado suficientes argumentos\n");
    return 1;
  } else if (atoi(argv[1]) <= 0 && atoi(argv[2]) <= 0) {
    printf("Los argumentos son menores o iguales a 0\n");
    return 1;
  }
  // Captura de los valores ingresados como argumentos.
  int N = atoi(argv[1]);
  int H = atoi(argv[2]);

  // Creación de punteros para hacer referencia a diferentes áreas de memoria
  // dentro de MEM_CHUNK[RESERVA].
  double *mA, *mB, *mC;

  // Definición de las áreas de memoria a las que apuntarán los punteros.
  mA = MEM_CHUNK;
  mB = mA + (N * N);
  mC = mB + (N * N);
  // Inicialización de matrices.
  inicializarMatrices(N, mA, mB, mC);

  // Impresión de cada una de las matrices.
  printf("\n");
  printf("Matriz A\n");
  imprimirMatriz(N, mA);
  printf("\n");
  printf("Matriz B\n");
  imprimirMatriz(N, mB);
  // printf("Matriz C\n");
  // imprimirMatriz(N, mC);
  /*Instancia de un puntero de tipo datosMM.
  Se asigna su tamaño en memoria mediante malloc*/
  struct datosMM *valoresMM = (struct datosMM *)malloc(sizeof(struct datosMM));
  // struct datosMM* valoresMM;
  valoresMM->N = N;
  valoresMM->H = H;
  valoresMM->mA = mA;
  valoresMM->mB = mB;
  valoresMM->mC = mC;
  // /*Creación de tantos hilos de ejecución como se hayan recibido como
  // argumento*/
  pthread_t hilos[H];
  printf("\n");
  printf("Matriz Resultante\n");

  for (int h = 0; h < H; h++) {
    /*Función para la creación de hilos de ejecución.*/
    pthread_create(&hilos[h], NULL, multiplicacionMatriz, valoresMM);
  }
  /*Espera la finalización de cada uno de los hilos*/
  for (int h = 0; h < H; h++) {
    pthread_join(hilos[h], NULL);
  }

  printf("\nFin del programa\n");
  // return 0;
  pthread_exit(NULL);
  free(valoresMM);
}