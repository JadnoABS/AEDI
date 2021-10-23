/**************************************************************/
/* Aluno: Jadno Augusto Barbosa da Silva
/* Número USP: 12608618
/* Disciplina/Ano/EP: ACH2023/2021/EP1
/**************************************************************/




/*
 *  Duvidas sobre o EP
 *  - Quantas casas decimais de precisao no printf
 *  - Eh (0, true) e (1, false) mesmo?
 *  - A derivada do exemplo do PDF nao esta em ordem
 * */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum operacoes {Soma = 1, Subtracao, Multiplicacao, Derivada, Raiz, Resolucao, Impressao, Grau} operacao;

typedef struct termo {
  double coeficiente;
  int expoente;
  struct termo* prox;
  struct termo* ant;
} TERMO;

typedef struct {
  TERMO* cabeca;
} POLINOMIO;


/*---------- Funcoes basicas de uma lista ligada ---------- */


void inicializarPolinomio(POLINOMIO* pol) {
  pol->cabeca = (TERMO*) malloc(sizeof(TERMO));
  pol->cabeca->prox = pol->cabeca;
  pol->cabeca->ant = pol->cabeca;
  return;
}

int tamanhoDoPolinomio(POLINOMIO* polinomio) {
  int i = 0;
  TERMO* elem = polinomio->cabeca;

  while(elem->prox != polinomio->cabeca) {
    elem = elem->prox;
    i++;
  }

  return i;
}

TERMO* buscaSeqOrd(POLINOMIO* polinomio, int expoente, TERMO** ant) {
  polinomio->cabeca->expoente = expoente;
  TERMO* termo = polinomio->cabeca->prox;
  *ant = polinomio->cabeca;

  while(termo->expoente > expoente) {
    *ant = termo;
    termo = termo->prox;
  }

  if(termo->expoente == expoente && termo != polinomio->cabeca) return termo;
  return NULL;
}


bool excluirTermo(POLINOMIO* polinomio, int expoente) {
  TERMO* ant;
  TERMO* termo = buscaSeqOrd(polinomio, expoente, &ant);

  if(!termo) return false;

  termo->prox->ant = termo->ant;
  termo->ant->prox = termo->prox;
  free(termo);

  return true;
}

bool inserirTermo(POLINOMIO* pol, double coeficiente, int expoente) {
  TERMO* ant;
  TERMO* termo = buscaSeqOrd(pol, expoente, &ant);

  if(termo) {
    termo->coeficiente += coeficiente;
    if(!termo->coeficiente) excluirTermo(pol, termo->expoente);
    return true;
  };

  termo = (TERMO*) malloc(sizeof(TERMO));

  termo->ant = ant;
  termo->prox = ant->prox;
  termo->prox->ant = termo;
  ant->prox = termo;
  termo->coeficiente = coeficiente;
  termo->expoente = expoente;

  return true;
}


/*---------- Operacoes de polinomios ---------- */


POLINOMIO* somar(POLINOMIO* pol1, POLINOMIO* pol2) {
  POLINOMIO* resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO));
  inicializarPolinomio(resultado);

  TERMO* termo = pol1->cabeca->prox;
  while(termo != pol1->cabeca) {
    inserirTermo(resultado, termo->coeficiente, termo->expoente);
    termo = termo->prox;
  }
  termo = pol2->cabeca->prox;
  while(termo != pol2->cabeca) {
    inserirTermo(resultado, termo->coeficiente, termo->expoente);
    termo = termo->prox;
  }

  return resultado;
}

POLINOMIO* subtrair(POLINOMIO* pol1, POLINOMIO* pol2) {
  POLINOMIO* resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO));
  inicializarPolinomio(resultado);

  TERMO* termo = pol1->cabeca->prox;
  while(termo != pol1->cabeca) {
    inserirTermo(resultado, termo->coeficiente, termo->expoente);
    termo = termo->prox;
  }
  termo = pol2->cabeca->prox;
  while(termo != pol2->cabeca) {
    inserirTermo(resultado, -(termo->coeficiente), termo->expoente);
    termo = termo->prox;
  }

  return resultado;
}

POLINOMIO* multiplicar(POLINOMIO* pol1, POLINOMIO* pol2) {
  POLINOMIO* resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO));
  inicializarPolinomio(resultado);

  TERMO* termo1 = pol1->cabeca->prox;
  while(termo1 != pol1->cabeca) {
    TERMO* termo2 = pol2->cabeca->prox;

    while(termo2 != pol2->cabeca) {
      double coeficiente = termo1->coeficiente * termo2->coeficiente;
      int expoente = termo1->expoente + termo2->expoente;
      inserirTermo(resultado, coeficiente, expoente);
      termo2 = termo2->prox;
    }
    termo1 = termo1->prox;
  }

  return resultado;
}

POLINOMIO* derivar(POLINOMIO* pol) {
  POLINOMIO* resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO));
  inicializarPolinomio(resultado);

  TERMO* termo = pol->cabeca->prox;
  while(termo != pol->cabeca) {
    double coeficiente = termo->expoente * termo->coeficiente;
    int expoente = termo->expoente - 1;

    if(expoente >= 0 && coeficiente){
      inserirTermo(resultado, coeficiente, expoente);
    }

    termo = termo->prox;
  }

  return resultado;
}

int verificarRaiz(POLINOMIO* pol, int raiz) {
  double resultado = 0;
  TERMO* termo = pol->cabeca->prox;

  while(termo != pol->cabeca) {
    resultado += termo->coeficiente * pow(raiz, termo->expoente);
    termo = termo->prox;
  }

  if(resultado) return 1;
  return 0;
}


double* calcularRaiz(POLINOMIO* pol) {
  double* resultado = (double*) malloc(sizeof(double) * 2);
  TERMO* termo = pol->cabeca->prox;

  if(termo->expoente != 2 || termo == pol->cabeca){
    resultado[0] = 99999;
    resultado[1] = -99999;
    return resultado;
  }

  double a = 0; double b = 0; double c = 0;
  while(termo != pol->cabeca){
    if(termo->expoente == 2) a = termo->coeficiente;
    if(termo->expoente == 1) b = termo->coeficiente;
    if(termo->expoente == 0) c = termo->coeficiente;

    termo = termo->prox;
  }

  double delta = (b*b) - (4 * a * c);
  double raizDelta = sqrt(delta);
  if(raizDelta * raizDelta != delta){
    resultado[0] = 99999;
    resultado[1] = -99999;
    return resultado;
  }

  resultado[0] = (-b + raizDelta)/(2*a);
  resultado[1] = (-b - raizDelta)/(2*a);
  return resultado;
}

int grauDoPolinomio(POLINOMIO* pol) {
  if(pol->cabeca->prox != pol->cabeca){
    return pol->cabeca->prox->expoente;
  }
  return 0;
}


/*---------- Impressoes ---------- */


void imprimirPolinomio(POLINOMIO* pol) {
  printf("%d", tamanhoDoPolinomio(pol));
  TERMO* termo = pol->cabeca->prox;

  while(termo != pol->cabeca){
    printf(" %.lf %d", termo->coeficiente, termo->expoente);
    termo = termo->prox;
  }

  printf("\n");
  return;
}

void imprimirPolinomioFormatado(POLINOMIO* pol) {
  bool printCoeficiente;
  bool printVariavel;
  TERMO* termo = pol->cabeca->prox;

  while(termo != pol->cabeca){
    printVariavel = termo->expoente;
    printCoeficiente = termo->coeficiente && (termo->coeficiente != 1 || !printVariavel);

    if(printCoeficiente) printf("%.2lf", (double)abs(termo->coeficiente));
    if(printVariavel) {
      if(termo->expoente > 1) printf("x^%d", termo->expoente);
      else printf("x");
    }

    termo = termo->prox;
    if(termo->coeficiente != 0) {
      char sinal = termo->coeficiente > 0 ? '+' : '-';
      printf("%c", sinal);
    }
  }

  printf("\n");
  return;
}


/*---------- Leitura e insercao ordenada do polinomio ----------*/


void lerEInserirNoPolinomio(POLINOMIO* pol) {
  int numTermos;

  scanf("%d", &numTermos);

  for(int j = 0; j < numTermos; j++) {
    double coeficiente; int expoente;
    scanf("%lf %d", &coeficiente, &expoente);
    inserirTermo(pol, coeficiente, expoente);
  }
}


/*---------- MAIN ----------*/


int main() {
  int cases;
  scanf("%d", &cases);

  POLINOMIO* polinomio1 = NULL;
  POLINOMIO* polinomio2 = NULL;
  POLINOMIO* resultado = NULL;

  for(int i = 0; i < cases; i++) {
    scanf("%d", &operacao);
    polinomio1 = (POLINOMIO*) malloc(sizeof(POLINOMIO));

    inicializarPolinomio(polinomio1);
    lerEInserirNoPolinomio(polinomio1);


    switch(operacao) {
      case Soma:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = somar(polinomio1, polinomio2);
        printf("%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Subtracao:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = subtrair(polinomio1, polinomio2);
        printf("%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Multiplicacao:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = multiplicar(polinomio1, polinomio2);
        printf("%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Derivada:
        resultado = derivar(polinomio1);
        printf("%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Raiz:
        double raiz;
        scanf("%lf", &raiz);

        printf("%d\n", operacao);
        printf("%d\n", verificarRaiz(polinomio1, raiz));
        break;
      case Resolucao:
        double* raizes = calcularRaiz(polinomio1);

        printf("%d\n", operacao);
        printf("%.2lf %.2lf\n", raizes[0], raizes[1]);
        free(raizes);
        break;
      case Impressao:
        printf("%d\n", operacao);
        imprimirPolinomioFormatado(polinomio1);
        break;
      case Grau:
        printf("%d\n", operacao);
        printf("%d\n", grauDoPolinomio(polinomio1));
        break;
    }

    if(polinomio1){
      free(polinomio1);
      polinomio1 = NULL;
    }
    if(polinomio2){
      free(polinomio2);
      polinomio2 = NULL;
    }
    if(resultado){
      free(resultado);
      resultado = NULL;
    }
  }

  return 0;
}

