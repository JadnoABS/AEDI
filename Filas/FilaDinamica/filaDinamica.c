#include "filaDinamica.h"

void inicializarFila(FILA* fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

int tamanhoDaFila(FILA* fila) {
  NO* elem = fila->inicio;
  int tamanho = 0;

  while(elem) {
    elem = elem->prox;
    tamanho++;
  }

  return tamanho;
}

void inserirNaFila(FILA* fila, TIPOCHAVE ch) {
  NO* elem = (NO*) malloc(sizeof(NO));

  elem->chave = ch;
  elem->prox = NULL;
  if(fila->fim) fila->fim->prox = elem;
  else fila->inicio = elem;

  fila->fim = elem;

  return;
}

TIPOCHAVE removerDaFila(FILA* fila) {
  NO* elem = fila->inicio;
  if(!elem) return -1;

  TIPOCHAVE ch = elem->chave;
  fila->inicio = elem->prox;
  free(elem);

  if(!fila->inicio) fila->fim = NULL;

  return ch;
}
