#include "arvoresBinDinamicas.h"


void inicializarArvore(NO* *raiz) {
  *raiz = NULL;
}

bool arvoreVazia(NO* raiz) {
  if(raiz) return false;
  return true;
}

bool inserirNo(NO* *raiz, NO* pai, TIPOCHAVE ch, LADO pos) {
  if(pai){
    if(pos == esq && pai->esq) return false;
    if(pos == dir && pai->dir) return false;
  }
    
  NO* elem = (NO*) malloc(sizeof(NO));
  elem->chave = ch;
  elem->esq = NULL;
  elem->dir = NULL;

  if(!pai) *raiz = elem;
  else {
    switch(pos){
      case esq:
        pai->esq = elem;
        break;
      case dir:
        pai->dir = elem;
        break;
    }
  }

  return true;
}

void percorrerArvore(NO* raiz) {

  if(!raiz) return;

  printf("%d\n", raiz->chave);

  percorrerArvore(raiz->esq);
  percorrerArvore(raiz->dir);

  return;
}


int main() {

  NO* raiz;
  inicializarArvore(&raiz);

  inserirNo(&raiz, NULL, 6, 0);
  inserirNo(&raiz, raiz, 3, 0);
  inserirNo(&raiz, raiz, 8, 1);
  inserirNo(&raiz, raiz->esq, 5, 0);
  inserirNo(&raiz, raiz->esq, 1, 1);
  inserirNo(&raiz, raiz->dir, 2, 0);
  inserirNo(&raiz, raiz->dir, 9, 1);

  percorrerArvore(raiz);

  return 0;

}

