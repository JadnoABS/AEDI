#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int TIPOCHAVE;

typedef struct no {
  TIPOCHAVE chave;
  struct no* ant;
  struct no* prox;
} NO;

typedef struct {
  NO* cabeca;
} LISTA;


void inicializarListaDuplamenteLigada(LISTA* lista);

int tamanhoDaLista(LISTA* lista);

void exibirLista(LISTA* lista);

NO* buscaSeqOrd(LISTA* lista, TIPOCHAVE ch, NO** ant);

bool insercaoOrd(LISTA* lista, TIPOCHAVE ch);

TIPOCHAVE primeiroElemento(LISTA* lista);

TIPOCHAVE ultimoElemento(LISTA* lista);

TIPOCHAVE enesimoElemento(LISTA* lista, int n);

void popularLista(LISTA* lista, int tamanho);

bool excluirElemento(LISTA* lista, TIPOCHAVE ch);

void destruirLista(LISTA* lista);
