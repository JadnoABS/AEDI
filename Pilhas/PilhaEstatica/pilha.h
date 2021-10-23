#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    int topo;
    REGISTRO A[MAX];
} Pstatic;


void inicializarPilhaEstatica(Pstatic* pilha);

bool pilhaCheia(Pstatic pilha);

bool push(Pstatic* pilha, TIPOCHAVE ch);

TIPOCHAVE pop(Pstatic* pilha);
