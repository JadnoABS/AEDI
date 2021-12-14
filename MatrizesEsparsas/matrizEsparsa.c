#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLIN 100
#define MAXCOL 100

typedef int TIPOINFO

// Implementacao de matriz esparsa cruzada

typedef struct no {
  int linha;
  int coluna;
  TIPOINFO info;
  struct no* proxL;
  struct no* proxC;
} NO;


typedef stuct {
  NO* linhas[MAXLIN+1];
  NO* colunas[MAXCOL+1];
} MATRIZ;


void inicializarMatriz(MATRIZ* matriz) {
  for(int i = 0; i <= MAXLIN; i++)
    matriz->linhas[i] = NULL;
  for(int i = 0; i <= MAXCOL; i++)
    matriz->colunas[i] = NULL;
}

int contaElementos(MATRIZ matriz) {
  int nElem = 0;
  for(int i = 1; i <= MAXLIN; i++){
    NO* elem = matriz.linhas[i];
    while(elem){
      nElem++;
      elem = elem->proxL;
    }
  }

  return nElem;
}

TIPOINFO obtemValor(MATRIZ matriz, int i, int j) {
  if ((i < 1) || (j < 1) || (i > MAXLIN) || (j > MAXCOL)) {
    fprintf(stderr, "i,j devem ser maiores que zero e menores ou iguais a %d e %d, respectivamente, na função alteraValor", MAXLIN, MAXCOL);
    exit(1);
  }

  NO* elem;

  if(i < j) {
    elem = matriz.colunas[i];
    while(elem && elem->linha <= i){
      if(elem->linha == i) return elem->info;
      elem = elem->proxC;
    }

    return 0;
  }
  else {
    elem = matriz.linhas[i];
    while(elem && elem->coluna <= j){
      if(elem->coluna == j) return elem->info;
      elem = elem->proxL;
    }

    return 0;
  }
}

