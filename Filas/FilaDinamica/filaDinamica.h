#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int TIPOCHAVE;

typedef struct no {
  TIPOCHAVE chave;
  struct no* prox;
} NO;

typedef struct {
  NO* inicio;
  NO* fim;
} FILA;


void inicializarFila(FILA* fila);

int tamanhoDaFila(FILA* fila);

void inserirNaFila(FILA* fila, TIPOCHAVE ch);

TIPOCHAVE removerDaFila(FILA* fila);
