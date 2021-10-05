#include "listaLigCircular.h"

void inicializarListaLigadaCircular(LISTA* lista) {
  NO* cabeca = (NO*) malloc(sizeof(NO));
  cabeca->prox = cabeca;

  lista->cabeca = cabeca;
  return;
}

int tamanhoDaLista(LISTA* lista) {
  int i = 0;
  NO* elem = lista->cabeca;

  while(elem->prox != lista->cabeca) {
    elem = elem->prox;
    i++;
  }

  return i;
}

void exibirLista(LISTA* lista) {
  NO* item = lista->cabeca->prox;

  printf("------\n");
  while(item != lista->cabeca){
    printf("| ");
    printf("%2.d", item->chave);
    printf(" |\n");

    item = item->prox;

  }
  printf("------\n");
  return;
}

NO* buscaSeqOrd(LISTA* lista, TIPOCHAVE ch, NO** ant) {
  lista->cabeca->chave = ch;
  NO* elem = lista->cabeca->prox;
  *ant = lista->cabeca;

  while(elem->chave < ch) {
    *ant = elem;
    elem = elem->prox;
  }

  if(elem->chave == ch && elem != lista->cabeca) return elem;
  return NULL;
}

bool insercaoOrd(LISTA* lista, TIPOCHAVE ch) {
  NO* ant;
  NO* elem = buscaSeqOrd(lista, ch, &ant);

  if(elem) return false;

  elem = (NO*) malloc(sizeof(NO));

  elem->prox = ant->prox;
  ant->prox = elem;
  elem->chave = ch;

  return true;
}

TIPOCHAVE primeiroElemento(LISTA* lista) {
  if(lista->cabeca->prox != lista->cabeca) {
    return lista->cabeca->prox->chave;
  }

  return -1;
}

TIPOCHAVE ultimoElemento(LISTA* lista) {
  NO* elem = lista->cabeca->prox;


  while(elem->prox != lista->cabeca) {
    elem = elem->prox;
  }

  if(elem != lista->cabeca) return elem->chave;
  return -1;
}

TIPOCHAVE enesimoElemento(LISTA* lista, int n) {
  NO* elem = lista->cabeca;
  int i = 0;

  while(i < n && elem->prox != lista->cabeca) {
    elem = elem->prox;
    i++;
  }

  if(elem != lista->cabeca) return elem->chave;
  return -1;
}

void popularLista(LISTA* lista, int tamanho) {
  time_t t;
  srand((unsigned int) time(&t));
  int i = 0;
  bool inserido;

  do {
    inserido = insercaoOrd(lista, rand() % 100);
    i++;
  } while(i < tamanho);

  return;
}

bool excluirElemento(LISTA* lista, TIPOCHAVE ch) {
  NO* ant;
  NO* elem = buscaSeqOrd(lista, ch, &ant);

  if(!elem) return false;

  ant->prox = elem->prox;
  free(elem);

  return true;
}

void destruirLista(LISTA* lista) {
  NO* elem = lista->cabeca->prox;
  NO* prox;

  while(elem != lista->cabeca) {
    prox = elem->prox;
    free(elem);
    elem = prox;
  }

  lista->cabeca->prox = lista->cabeca;

  return;
}
