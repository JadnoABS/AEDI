#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

enum operacoes {Criar = 1, Inserir, Excluir, CalcBal, VerificarAVL} operacao;

typedef struct no {
  TIPOCHAVE chave;
  struct no* esq;
  struct no* dir;
  int bal;
} NO;

FILE* entrada;
FILE* saida;



void inicializarAVL(NO* *raiz) {
  *raiz = NULL;
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
  r->dir = q;

  switch(r->bal) {
    case -1:
      p->bal = 0;
      q->bal = 1;
      break;
    case 0:
      p->bal = 0;
      q->bal = 0;
      break;
    case 1:
      p->bal = -1;
      q->bal = 0;
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
  r->esq = q;
  r->dir = p;

  switch(r->bal) {
    case -1:
      p->bal = 1;
      q->bal = 0;
      break;
    case 0:
      p->bal = 0;
      q->bal = 0;
      break;
    case 1:
      p->bal = 0;
      q->bal = -1;
      break;
  }

  r->bal = 0;
  return r;
}


NO* inserirElemento(NO* raiz, TIPOCHAVE chave, bool* ajustar) {

  if(!raiz){
    raiz = (NO*) malloc(sizeof(NO));
    raiz->chave = chave;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->bal = 0;
    *ajustar = true;
  } else {
    if(chave < raiz->chave){
      raiz->esq = inserirElemento(raiz->esq, chave, ajustar);
      if(*ajustar){
        switch(raiz->bal){
          case 1:
            raiz->bal = 0;
            *ajustar = false;
            break;
          case 0:
            raiz->bal = -1;
            break;
          case -1:
            if(raiz->esq->bal == -1){
              raiz = rotacaoDireita(raiz);
            } else {
              raiz = rotacaoEsqDir(raiz);
            }
            *ajustar = false;
            break;
        }
      }

    } else {
      raiz->dir = inserirElemento(raiz->dir, chave, ajustar);

      if(*ajustar){
        switch(raiz->bal){
          case -1:
            raiz->bal = 0;
            *ajustar = false;
            break;
          case 0:
            raiz->bal = 1;
            break;
          case 1:
            if(raiz->dir->bal == 1){
              raiz = rotacaoEsquerda(raiz);
            } else {
              raiz = rotacaoDirEsq(raiz);
            }
            *ajustar = false;
            break;
        }
      }
    }
  }

  return raiz;
}


void imprimirAVL(NO* raiz) {

  fprintf(saida, "(");
  if(raiz){
    fprintf(saida, "%d", raiz->chave);
    if(raiz->esq || raiz->dir){
      imprimirAVL(raiz->esq);
      imprimirAVL(raiz->dir);
    }
  }
  fprintf(saida, ")");
}


/* -------------- APAGAR ESSA PARTE DEPOIS!!! ----------------*/

typedef struct nofila {
  NO* no;
  struct nofila* prox;
} NOFILA;

typedef struct {
  NOFILA* inicio;
  NOFILA* fim;
} FILA;


void inicializarFila(FILA* fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

void inserirNaFila(FILA* fila, NO* no) {
  NOFILA* elem = (NOFILA*) malloc(sizeof(NOFILA));

  elem->no = no;
  elem->prox = NULL;
  if(fila->fim) fila->fim->prox = elem;
  else fila->inicio = elem;
  fila->fim = elem;

  return;
}

NO* removerDaFila(FILA* fila) {
  NOFILA* elem = fila->inicio;
  if(!elem) return NULL;

  NO* no = elem->no;
  fila->inicio = elem->prox;
  free(elem);

  if(!fila->inicio) fila->fim = NULL;

  return no;
}



void imprimirArvoreTeste(NO* raiz) {
  FILA f;
  NO* p = raiz;
  inicializarFila(&f);
  int i = 1;
  int j = 1;
  while( (p) || (f.inicio) ) {
    if(p->esq) inserirNaFila(&f, p->esq);
    if(p->dir) inserirNaFila(&f, p->dir);
    printf("%d ", p->chave);
    if((i+1) % (2*j) == 0){
      printf("\n");
      j *= 2;
    }
    i++;
    p = NULL;
    if(f.inicio) p = removerDaFila(&f);
  }
}


/* -------------- APAGAR ESSA PARTE DEPOIS!!! ----------------*/



void excluirAVL(NO* raiz) {

  if(raiz->esq) excluirAVL(raiz->esq);
  if(raiz->dir) excluirAVL(raiz->dir);
  free(raiz);
}



int main(int argc, char *argv[]) {

  if(argc >= 2){
    entrada = fopen(argv[1], "r");
  }
  if(argc >= 3){
    saida = fopen(argv[2], "w");
  }

  int cases;
  fscanf(entrada, "%d", &cases);
  printf("%d\n", cases);

  for(int i = 0; i < cases; i++){
    fscanf(entrada, "%d", &operacao);
    printf("%d\n", operacao);

    switch(operacao){
      case Criar:
        NO* raiz;
        inicializarAVL(&raiz);

        int chave; char aux;
        do {
          fscanf(entrada, "%d%c", &chave, &aux);
          bool ajustar = false;
          raiz = inserirElemento(raiz, chave, &ajustar);
          imprimirArvoreTeste(raiz);
          printf("\n");
        } while(aux != '\n');

        imprimirArvoreTeste(raiz);
        imprimirAVL(raiz);

        if(raiz) excluirAVL(raiz);
        break;
      case Inserir:
        break;
      case Excluir:
        break;
      case CalcBal:
        break;
      case VerificarAVL:
        break;
    }
    

  }

}


