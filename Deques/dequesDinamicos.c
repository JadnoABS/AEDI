#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>




#define MAX 50

#define NUMERO_INVALIDO -1

typedef int TIPOCHAVE;

typedef struct estrutura {
  TIPOCHAVE chave;
  struct estrutura *prox;
  struct estrutura *ant;
} NO;

typedef struct {
  NO *inicio1;
  NO *inicio2;
} DEQUE;

void inicializarDeque(DEQUE *d) {
  d->inicio1 = NULL;
  d->inicio2 = NULL;
}

int tamanhoDeque(DEQUE d) {
  NO *aux = d.inicio1;
  int i = 0;

  while (aux) {
    i++;
    aux = aux->prox;
  }

  return i;
}

void entrarDeque1(TIPOCHAVE ch, DEQUE *d) {
  NO *novo = (NO *)malloc(sizeof(NO));

  novo->chave = ch;
  novo->ant = NULL;
  novo->prox = d->inicio1;

  if (d->inicio1)
    d->inicio1->ant = novo;
  else
    d->inicio2 = novo;

  d->inicio1 = novo;
}

void entrarDeque2(TIPOCHAVE ch, DEQUE *d) {
  NO *novo = (NO *)malloc(sizeof(NO));

  novo->chave = ch;
  novo->ant = d->inicio2;
  novo->prox = NULL;

  if (d->inicio2)
    d->inicio2->prox = novo;
  else
    d->inicio1 = novo;

  d->inicio2 = novo;
}

TIPOCHAVE sairDeque1(DEQUE *d) {
  NO *aux;

  if (!d->inicio1) // caso lista vazia
    return -1;

  aux = d->inicio1;
  TIPOCHAVE ch = aux->chave;
  d->inicio1 = d->inicio1->prox;
  free(aux);

  if (!d->inicio1)
    d->inicio2 = NULL;
  else
    d->inicio1->ant = NULL;

  return ch;
}

TIPOCHAVE sairDeque2(DEQUE *d) {
  NO *aux;

  if (!d->inicio2) // caso lista vazia
    return -1;

  aux = d->inicio2;
  TIPOCHAVE ch = aux->chave;
  d->inicio2 = d->inicio2->ant;
  free(aux);

  if (!d->inicio2)
    d->inicio1 = NULL;
  else
    d->inicio2->prox = NULL;

  return ch;
}


void destruirDeque(DEQUE *d) {
  while (d->inicio1)
    sairDeque1(d);
}

