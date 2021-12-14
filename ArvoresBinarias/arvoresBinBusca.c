#include "arvoresBinDinamicas.h"


NO* buscaNo(NO* raiz, TIPOCHAVE ch, NO* *pai) {

  NO* elem = raiz;
  *pai = NULL;

  while(elem && elem->chave != ch){
    *pai = elem;
    if(elem->chave < ch) elem = elem->dir;
    if(elem->chave > ch) elem = elem->esq;
  }

  return elem;
}

NO* buscaNoRecur(NO* raiz, TIPOCHAVE ch, NO* *pai) {

  if(raiz->chave == ch) return raiz;

  NO* elem = NULL;
  *pai = raiz;

  if(raiz->chave < ch) elem = buscaNoRecur(raiz->dir, ch, pai); 
  else elem = buscaNoRecur(raiz->esq, ch, pai); 

  return elem;

}

bool insercao(NO* raiz, TIPOCHAVE ch) {

  NO* *pai = NULL;
  NO* elem = buscaNo(raiz, ch, pai);

  if(elem) return false;

  elem = (NO*) malloc(sizeof(NO));
  elem->chave = ch;
  elem->esq = NULL;
  elem->dir = NULL;

  if(*pai->ch < ch) *pai->dir = elem;
  else *pai->esq = elem;

  return true;

}

NO* insercaoRecur(NO* raiz, TIPOCHAVE ch) {

  NO* elem;

  if(!raiz){
    novo = (NO*) malloc(sizeof(NO));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->chave = ch;
    return novo;
  }

  if(raiz->chave < ch) raiz->dir = insercaoRecur(raiz->dir, ch);
  else raiz->esq = insercaoRecur(raiz->esq, ch);

  return raiz;

}
