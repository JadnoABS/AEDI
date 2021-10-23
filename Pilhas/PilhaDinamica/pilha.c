#include "pilha.h"

void inicializarPdinam(Pdinam *p) { p->topo = NULL; }

int tamanhoPdinam(Pdinam p) {
  int i = 0;
  Registro *aux = p.topo;

  while (!aux) {
    i++;
    aux = aux->ant;
  }

  return i;
}

void push(TIPOCHAVE ch, Pdinam *p) {
  Registro *novoReg = (Registro *)malloc(sizeof(Registro));

  novoReg->ant = p->topo;
  p->topo = novoReg;
  novoReg->chave = ch;
}

TIPOCHAVE pop(Pdinam *p) {
  if (!p->topo)
    return -1;

  Registro *aux = p->topo;
  TIPOCHAVE chave = p->topo->chave;
  p->topo = p->topo->ant;

  free(aux);

  return chave;
}
