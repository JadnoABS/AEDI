#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef int TIPOCHAVE;


typedef struct {
  TIPOCHAVE chave;
  int prox;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX];
  int inicio;
  int proxDisponivel;
} LISTA;

void inicializarListaLigadaEstatica(LISTA* lista);


void exibirLista(LISTA* lista);

int tamanhoDaLista(LISTA* lista);

TIPOCHAVE primeiroElemento(LISTA* lista);

TIPOCHAVE ultimoElemento(LISTA* lista);

TIPOCHAVE nesimoElemento(LISTA* lista, int n);

void destruirLista(LISTA* lista);

TIPOCHAVE buscaSeqOrd(LISTA* lista, TIPOCHAVE ch, int* ant);

void insercaoOrd(REGISTRO reg, LISTA* lista);

void popularLista(LISTA* lista, int tamanho);
