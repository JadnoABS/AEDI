#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum { esq, dir } LADO;

typedef struct no {
  TIPOCHAVE chave;
  struct no* esq;
  struct no* dir;
  int bal;
} NO;


void inicializarAVL(NO* *raiz) {
  *raiz = NULL;

  *raiz->esq = NULL;
  *raiz->dir = NULL;
  *raiz->bal = 0;
}


NO* rotacaoDireita(NO* p) {
  NO* q = p->esq;
  p->esq = q->dir;
  q->dir = p;
  p->bal = 0;
  q->bal = 0;
  return q;
}

NO* rotacaoEsquerda(NO* p) {
  NO* q = p->dir;
  p->dir = q->esq;
  q->esq = p;
  p->bal = 0;
  q->bal = 0;
  return q;
}

NO* rotacaoDirEsq(NO* p) {
  NO* q = p->dir;
  NO* r = q->esq;
  q->esq = r->dir;
  p->dir = r->esq;
  r->esq = p;
  r->dir = u;

  switch(r->bal) {
    case -1:
      p->bal = 0;
      u->bal = 1;
      break;
    case 0:
      p->bal = 0;
      u->bal = 0;
      break;
    case 1:
      p->bal = -1;
      u->bal = 0;
      break;
  }

  r->bal = 0;
  return r;
}

NO* rotacaoEsqDir(NO* p) {
  NO* q = p->esq;
  NO* r = q->dir;
  q->dir= r->esq;
  p->esq = r->dir;
  r->esq = u;
  r->dir = p;

  switch(r->bal) {
    case -1:
      p->bal = 1;
      u->bal = 0;
      break;
    case 0:
      p->bal = 0;
      u->bal = 0;
      break;
    case 1:
      p->bal = 0;
      u->bal = -1;
      break;
  }

  r->bal = 0;
  return r;
}

NO* insercaoAVL(NO* p, TIPOCHAVE ch, bool* ajustar) {

  if(!p){
    p = (NO*) malloc(sizeof(NO));
    p->esq = NULL;
    p->dir = NULL;
    p->bal = 0;
    p->chave = ch;
  } else {

    if(p->chave > ch){
      p->esq = insercaoAVL(p->esq, ch, ajustar);

      if(*ajustar){
        switch(p->bal){
          case 1:
            p->bal = 0;
            *ajustar = false;
            break;
          case 0:
            p->bal = -1;
            break;
          case -1:
            if(p->esq->bal == -1){
              p = rotacaoDireita(p);
            } else {
              p = rotacaoEsqDir(p);
            }
            *ajustar = false;
            break;
        }
      }
    } else {
      p->dir = insercaoAVL(p->dir, ch, ajustar);

      if(*ajustar){
        switch(p->bal){
          case -1:
            p->bal = 0;
            *ajustar = false;
            break;
          case 0:
            p->bal = -1;
            *ajustar = false;
            break;
          case 1:
            if(p->dir->bal == 1){
              p = rotacaoEsquerda(p);
            } else {
              p = rotacaoDirEsq(p);
            }
            *ajustar = false;
            break;
        }
      }
    }
  } 

  return p;
}
