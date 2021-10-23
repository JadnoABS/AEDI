#include <stdbool.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct registro {
  TIPOCHAVE chave;
  struct registro *ant;
} Registro;

typedef struct {
  Registro *topo;
} Pdinam;


void inicializarPdinam(Pdinam *p);

int tamanhoPdinam(Pdinam p);

void push(TIPOCHAVE ch, Pdinam *p);

TIPOCHAVE pop(Pdinam *p);
