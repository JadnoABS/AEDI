#include "listaLigEstatica.h"

void inicializarListaLigadaEstatica(LISTA* lista) {
  lista->inicio = -1;
  lista->proxDisponivel = 0;

  int i = 0;
  while(i < MAX - 1) {
    lista->A[i].prox = i + 1;
    i++;
  }

  lista->A[MAX-1].prox = -1;
  return;
}

void exibirLista(LISTA* lista) {
  int i = lista->inicio;

  printf("------\n");
  while(i >= 0){
    printf("| ");
    printf("%2.d", lista->A[i].chave);
    printf(" |\n");

    i = lista->A[i].prox;
  }
  printf("------\n");
  return;
}

int tamanhoDaLista(LISTA* lista) {
  int tamanho = 0;
  int i = lista->inicio;
  while(i > -1){
    tamanho++;
    i = lista->A[i].prox;
  }

  return tamanho;
}

TIPOCHAVE primeiroElemento(LISTA* lista) {
  return lista->A[lista->inicio].chave;
}

TIPOCHAVE ultimoElemento(LISTA* lista) {
  int i;
  for(i = 0; i < tamanhoDaLista(lista); i++){
    if(lista->A[i].prox == -1){
      return lista->A[i].chave;
    }
  }

  return -1;
}

TIPOCHAVE nesimoElemento(LISTA* lista, int n) {
  int j = 1; int i = lista->inicio;
  while(j < n){
     i = lista->A[i].prox;
     j++;
  }

  return lista->A[i].chave;
}

void destruirLista(LISTA* lista) {
  lista->inicio = -1;
  lista->proxDisponivel = 0;
  return;
}


TIPOCHAVE buscaSeqOrd(LISTA* lista, TIPOCHAVE ch) {
  int i = lista->inicio;

  while(lista->A[i].chave < ch && i > -1){
    if(lista->A[i].prox > -1){
      i = lista->A[i].prox;
    } else return -1;
  }

  if(lista->A[i].chave == ch) return i;
  else return -1;
}

void insercaoOrd(REGISTRO reg, LISTA* lista) {
  int indiceReg = lista->proxDisponivel;
  if(lista->inicio < 0){
    lista->inicio = indiceReg;
    lista->proxDisponivel = lista->A[indiceReg].prox;
    lista->A[indiceReg].chave = reg.chave;
    lista->A[indiceReg].prox = -1;
    return;
  }

  int iSucessor = lista->inicio;
  int iAntecessor = -1;
  while(lista->A[iSucessor].chave < reg.chave){
    iAntecessor = iSucessor;
    iSucessor = lista->A[iSucessor].prox;
    if(iSucessor < 0){
      break;
    }
  }

  lista->proxDisponivel = lista->A[indiceReg].prox;

  lista->A[indiceReg].chave = reg.chave;
  lista->A[indiceReg].prox = iSucessor;

  if(iAntecessor >= 0){
    lista->A[iAntecessor].prox = indiceReg;
  } else lista->inicio = indiceReg;

  return;
}

void popularLista(LISTA* lista, int tamanho) {
  int i = 0;

  time_t t;
  srand((unsigned int) time(&t));

  REGISTRO reg;
  while(i < tamanho){
    reg.chave = rand() % 100;
    insercaoOrd(reg, lista);
    i++;
  }

  return;
}
