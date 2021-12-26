/**************************************************************/
/* Aluno: Jadno Augusto Barbosa da Silva
/* Número USP: 12608618
/* Disciplina/Ano/EP: ACH2023/2021/EP2
/**************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef int TIPOCHAVE;
typedef enum { esq, dir } LADO;

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


NO* inserirAVL(NO* raiz, TIPOCHAVE chave, bool* ajustar) {

  if(!raiz){
    raiz = (NO*) malloc(sizeof(NO));
    raiz->chave = chave;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->bal = 0;
    *ajustar = true;
  } else {
    if(chave < raiz->chave){
      raiz->esq = inserirAVL(raiz->esq, chave, ajustar);
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
      raiz->dir = inserirAVL(raiz->dir, chave, ajustar);

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


NO* maiorFilho(NO* raiz, LADO lado, NO* *pai) {
  if(lado == esq){
    if(raiz->esq){
      *pai = raiz;
      return maiorFilho(raiz->esq, dir, pai);
    }
    else return raiz;
  }
  if(lado == dir){
    if(raiz->dir){
      *pai = raiz;
      return maiorFilho(raiz->dir, dir, pai);
    }
    else return raiz;
  }
}

NO* menorFilho(NO* raiz, LADO lado, NO* *pai) {
  if(lado == esq){
    if(raiz->esq){
      *pai = raiz;
      return menorFilho(raiz->esq, esq, pai);
    }
    else return raiz;
  }
  if(lado == dir){
    if(raiz->dir){
      *pai = raiz;
      return menorFilho(raiz->dir, esq, pai);
    }
    else return raiz;
  }
}

NO* remocaoAVL(NO* raiz, TIPOCHAVE chave, bool* ajustar) {

  if(raiz->chave == chave){

    if(!raiz->dir || !raiz->esq){
      if(!raiz->dir && raiz->esq){
        NO* q = raiz->esq;
        free(raiz);
        *ajustar = true;
        return q;
      } else if(raiz->dir && !raiz->esq){
        NO* q = raiz->dir;
        free(raiz);
        *ajustar = true;
        return q;
      } else {
        free(raiz);
        *ajustar = true;
        return NULL;
      }
    }

    NO* p;
    NO* q = maiorFilho(raiz, esq, &p);

    if(p == raiz){
      q->dir = raiz->dir;
      free(raiz);
      return q;
    }

    q->dir = raiz->dir;
    p->dir = q->esq;
    q->esq = raiz->esq;
    free(raiz);
    return q;

  } else if(chave < raiz->chave){
    raiz->esq = remocaoAVL(raiz->esq, chave, ajustar);
    if(*ajustar){
      switch(raiz->bal){
        case 1:
          if(raiz->dir->bal == 1){
            raiz = rotacaoEsquerda(raiz);
          } else {
            raiz = rotacaoDirEsq(raiz);
          }
          *ajustar = false;
          break;
        case 0:
          raiz->bal = 1;
          *ajustar = false;
          break;
        case -1:
          raiz->bal = 0;
          break;
      }
    }

  } else {
    raiz->dir = remocaoAVL(raiz->dir, chave, ajustar);
    if(*ajustar){
      switch(raiz->bal){
        case -1:
          if(raiz->esq->bal == -1){
            raiz = rotacaoDireita(raiz);
          } else {
            raiz = rotacaoEsqDir(raiz);
          }
          *ajustar = false;
          break;
        case 0:
          raiz->bal = -1;
          *ajustar = false;
          break;
        case 1:
          raiz->bal = 0;
          break;
      }
    }
  }

  return raiz;
}



bool ehAVL(NO* raiz) {

  if(raiz->bal <= 1 && raiz->bal >= -1) {

    if(raiz->dir) {
      if(!ehAVL(raiz->dir)) return false;
    }
    if(raiz->esq) {
      if(!ehAVL(raiz->esq)) return false;
    }

    return true;
  }

  return false;
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


/* -----------------------------------------------------------*/



void excluirAVL(NO* raiz) {

  if(raiz->esq) excluirAVL(raiz->esq);
  if(raiz->dir) excluirAVL(raiz->dir);
  free(raiz);
}


NO* lerArvore(NO* raiz, bool* folha, int* altura) {

  // char parentese = getchar();
  char parentese = getc(entrada);
  // printf("%c ", parentese);
  if(parentese == ')') {
    *altura = 0;
    *folha = true; return NULL;
  };
  char a = getc(entrada);
  if(a == ')') return NULL;

  fseek(entrada, -sizeof(char), SEEK_CUR);

  int chave;
  fscanf(entrada, "%d", &chave);
  // printf("%d\n", chave);
  // scanf("%d", &chave);
  // printf("%c %d\n", parentese, chave);

  if(chave > 21000) {
    getc(entrada);
    // getchar();
    *folha = false;
    return NULL;
  };

  raiz = (NO*) malloc(sizeof(NO));
  raiz->chave = chave;
  raiz->bal = 0;

  int alturaEsq = 0; int alturaDir = 0;

  raiz->esq = lerArvore(raiz->esq, folha, altura);
  if(raiz->esq){
    (*altura)++;
    raiz->bal -= *altura;
    alturaEsq = *altura;
  }
  if(!(*folha)){
    raiz->dir = lerArvore(raiz->dir, folha, altura);
    if(raiz->dir){
      (*altura)++;
      raiz->bal += *altura;
      alturaDir = *altura;
    }
    getc(entrada);
    // getchar();
  } else { raiz->dir = NULL; }

  // printf("%d\n", raiz->bal);

  if(alturaEsq >= alturaDir) *altura = alturaEsq;
  else *altura = alturaDir;

  *folha = false;
  return raiz;

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
  fprintf(saida, "%d\n", cases);
  // printf("%d\n", cases);

  for(int i = 0; i < cases; i++){
    fscanf(entrada, "%d", &operacao);
    fprintf(saida, "%d\n", operacao);
    // printf("%d\n", operacao);
    NO* raiz;
    int chave;
    bool folha;
    bool ajustar;
    int altura;

    switch(operacao){
      case Criar:
        inicializarAVL(&raiz);

        char aux;
        do {
          fscanf(entrada, "%d%c", &chave, &aux);
          ajustar = false;
          raiz = inserirAVL(raiz, chave, &ajustar);
          imprimirArvoreTeste(raiz);
          printf("\n");
        } while(aux != '\n');

        // imprimirArvoreTeste(raiz);
        imprimirAVL(raiz);
        fprintf(saida, "\n");

        break;
      case Inserir:
        fscanf(entrada, "%d", &chave);
        getc(entrada);
        // scanf("%d", &ch);
        // getchar();

        folha = false;
        altura = 0;
        raiz = lerArvore(raiz, &folha, &altura);

        // imprimirAVL(raiz);
        // fprintf(saida, "\n");

        ajustar = false;
        raiz = inserirAVL(raiz, chave, &ajustar);

        // imprimirArvoreTeste(raiz);
        imprimirAVL(raiz);
        fprintf(saida, "\n");

        break;
      case Excluir:

        fscanf(entrada, "%d", &chave);
        getc(entrada);
        // scanf("%d", &ch);
        // getchar();

        folha = false;
        altura = 0;
        raiz = lerArvore(raiz, &folha, &altura);

        // imprimirAVL(raiz);
        // fprintf(saida, "\n");

        ajustar = false;
        raiz = remocaoAVL(raiz, chave, &ajustar);

        // imprimirArvoreTeste(raiz);
        imprimirAVL(raiz);
        fprintf(saida, "\n");

        break;
      case CalcBal:

        fscanf(entrada, "%d", &chave);
        getc(entrada);
        
        folha = false;
        altura = 0;
        raiz = lerArvore(raiz, &folha, &altura);

        NO* elem = raiz;
        while(elem->chave != chave){
          elem = chave > elem->chave ? elem->dir : elem->esq;
        }
        fprintf(saida, "%d\n", elem->bal);

        break;
      case VerificarAVL:
        getc(entrada);
        
        folha = false;
        altura = 0;
        raiz = lerArvore(raiz, &folha, &altura);

        if(ehAVL(raiz)) fprintf(saida, "T\n");
        else fprintf(saida, "F\n");

        break;
    }
    
    if(raiz) excluirAVL(raiz);
  }

}


