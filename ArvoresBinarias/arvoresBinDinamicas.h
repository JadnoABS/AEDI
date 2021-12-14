#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum { esq, dir } LADO;

typedef struct no {
  TIPOCHAVE chave;
  struct no* esq;
  struct no* dir;
} NO;


void inicializarArvore(NO* *raiz);

bool arvoreVazia(NO* raiz);

bool inserirNo(NO* *raiz, NO* pai, TIPOCHAVE ch, LADO pos);

void percorrerArvore(NO* raiz);
