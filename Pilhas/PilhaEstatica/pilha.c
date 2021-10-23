#include "pilha.h"


void inicializarPilhaEstatica(Pstatic* pilha) {
  p->topo = -1;
}

bool pilhaCheia(Pstatic pilha) {
  if(pilha.topo >= MAX-1) return true;
  return false;
}

bool push(Pstatic* pilha, TIPOCHAVE ch) {
  if(pilhaCheia(*pilha)) return false;

  pilha->topo++;
  pilha->A[pilha->topo].chave = ch;

  return true;
}

TIPOCHAVE pop(Pstatic* pilha) {
  if(pilha->topo < 0) return -1;

  TIPOCHAVE ch = pilha->A[pilha->topo].chave;
  pilha->topo--;

  return ch;
}
