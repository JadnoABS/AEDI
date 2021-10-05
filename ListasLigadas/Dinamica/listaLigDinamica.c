#include "listaLigDinamica.h"

void inicializarListaLigadaDinamica(LISTA* lista) {
  lista->inicio = NULL;
}

int tamanhoDaLista(LISTA* lista) {
  int i = 0;
  NO* elem = lista->inicio;
  while(elem) {
    elem = elem->prox;
    i++;
  }

  return i;
}

void exibirLista(LISTA* lista) {
  NO* item = lista->inicio;

  printf("------\n");
  while(item){
    printf("| ");
    printf("%2.d", item->chave);
    printf(" |\n");

    item = item->prox;
  }
  printf("------\n");
  return;
}

NO* buscaSeqOrd(LISTA* lista, TIPOCHAVE ch, NO** ant) {
  NO* elem = lista->inicio;
  *ant = NULL;
  if(!elem) return NULL;

  while(elem->chave < ch) {
    *ant = elem;
    elem = elem->prox;

    if(!elem) return NULL;
  }

  if(elem->chave == ch) {
    return elem;
  }
  return NULL;
}

bool insercaoOrd(LISTA* lista, TIPOCHAVE ch) {
  NO* ant;
  NO* elem = buscaSeqOrd(lista, ch, &ant);

  if(elem) {
    return false;
  }

  elem = (NO*) malloc(sizeof(NO));
  if(!ant) {
    elem->prox = lista->inicio;
    lista->inicio = elem;
  } else {
    elem->prox = ant->prox;
    ant->prox = elem;
  }

  elem->chave = ch;

  return true;
}

TIPOCHAVE primeiroElemento(LISTA* lista) {
  NO* elem = lista->inicio;
  if(elem) {
    return elem->chave;
  }

  return -1;
}

TIPOCHAVE ultimoElemento(LISTA* lista) {
  NO* elem = lista->inicio;
  if(!elem) return -1;

  while(elem->prox) {
    elem = elem->prox;
  }

  return elem->chave;
}

TIPOCHAVE enesimoElemento(LISTA* lista, int n) {
  NO* elem = lista->inicio;
  int i = 1;
  if(!elem) return -1;

  while(i < n) {
    elem = elem->prox;
    i++;
  }

  return elem->chave;
}

void popularLista(LISTA* lista, int tamanho) {
  time_t t;
  srand((unsigned int) time(&t));

  int i = 0;
  NO* item;
  NO* antecessor;

  while (i < tamanho) {
    bool inserted = insercaoOrd(lista, rand() % 100);
    if(!inserted) continue;

    i++;
  };

  return;
}

bool excluirElemento(LISTA* lista, TIPOCHAVE ch) {
  NO* ant;
  NO* elem = buscaSeqOrd(lista, ch, &ant);

  if(!elem) return false;
  if(!ant){
    lista->inicio = elem->prox;
  } else {
    ant->prox = elem->prox;
  }

  free(elem);
  return true;
}

void destruirLista(LISTA* lista) {

  NO* prox;
  NO* no = lista->inicio;

  while(no){
    prox = no->prox;
    free(no);
    no = prox;
  }

  lista->inicio = NULL;

  return;

}
