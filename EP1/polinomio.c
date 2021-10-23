/**************************************************************/
/* Aluno: Jadno Augusto Barbosa da Silva
/* Número USP: 12608618
/* Disciplina/Ano/EP: ACH2023/2021/EP1
/**************************************************************/



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


FILE* entrada;
FILE* saida;

/*---------- Funcoes basicas de uma lista duplamente ligada ---------- */


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


// O polinomio tera sempre ordem decrescente de expoente
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
    // Essa parte sera util para somar e subtrair dois polinomios
    termo->coeficiente += coeficiente;
    if(!termo->coeficiente) excluirTermo(pol, termo->expoente);
    return true;
  };

  if(!coeficiente) return false;

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

  // Ao inserir todos os termos dos dois polinomios
  // a insercaoOrdenada soma automaticamente os termos
  // de expoente igual
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
    // Neste a diferenca é que iremos inserir os termos da segunda lista
    // com o coeficiente negativo
    inserirTermo(resultado, -(termo->coeficiente), termo->expoente);
    termo = termo->prox;
  }

  return resultado;
}

POLINOMIO* multiplicar(POLINOMIO* pol1, POLINOMIO* pol2) {
  POLINOMIO* resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO));
  inicializarPolinomio(resultado);

  TERMO* termo1 = pol1->cabeca->prox;
  // Multiplica cada termo de pol1 por todos os de pol2
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
  // Deriva cada termo por vez e insere no resultado
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

  // Calculo do polinomio com x = raiz
  while(termo != pol->cabeca) {
    resultado += termo->coeficiente * pow(raiz, termo->expoente);
    termo = termo->prox;
  }

  // Caso o resultado nao zere, o numero nao é raiz
  if(resultado) return 1;
  return 0;
}


double* calcularRaiz(POLINOMIO* pol) {
  double* resultado = (double*) malloc(sizeof(double) * 2);
  TERMO* termo = pol->cabeca->prox;

  // Caso nao seja de grau 2
  if(termo->expoente != 2 || termo == pol->cabeca){
    resultado[0] = 99999;
    resultado[1] = -99999;
    return resultado;
  }

  // Separacao dos coeficientes
  double a = 0; double b = 0; double c = 0;
  while(termo != pol->cabeca){
    if(termo->expoente == 2) a = termo->coeficiente;
    if(termo->expoente == 1) b = termo->coeficiente;
    if(termo->expoente == 0) c = termo->coeficiente;

    termo = termo->prox;
  }

  // Formula de bhaskara
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
  // Apenas olhar o valor do primeiro expoente
  // pois o polinomio esta em ordem descrescente de expoente
  if(pol->cabeca->prox != pol->cabeca){
    return pol->cabeca->prox->expoente;
  }
  return 0;
}


/*---------- Impressoes ---------- */


void imprimirPolinomio(POLINOMIO* pol) {
  fprintf(saida, "%d", tamanhoDoPolinomio(pol));
  TERMO* termo = pol->cabeca->prox;

  while(termo != pol->cabeca){
    fprintf(saida, " %.lf %d", termo->coeficiente, termo->expoente);
    termo = termo->prox;
  }

  fprintf(saida, "\n");
  return;
}

void imprimirPolinomioFormatado(POLINOMIO* pol) {
  bool printCoeficiente;
  bool printVariavel;
  TERMO* termo = pol->cabeca->prox;

  while(termo != pol->cabeca){
    if(termo->coeficiente != 0) {
      char sinal = termo->coeficiente > 0 ? '+' : '-';

      // Printa apenas sinal negativo no primeiro termo
      // e printa qualquer um dos sinais nos outros termos
      if(termo->ant != pol->cabeca || sinal == '-')
        fprintf(saida, "%c", sinal);
    }

    // Booleanos para decidir se o coeficiente e a variavel precisarao ser printadas
    printVariavel = termo->expoente;
    printCoeficiente = termo->coeficiente && (termo->coeficiente > 1 || !printVariavel);

    if(printCoeficiente) fprintf(saida, "%.2lf", (double)abs(termo->coeficiente));
    if(printVariavel) {
      if(termo->expoente > 1) fprintf(saida, "x^%d", termo->expoente);
      else fprintf(saida, "x");
    }

    termo = termo->prox;
  }

  fprintf(saida, "\n");
  return;
}


/*---------- Leitura e insercao ordenada do polinomio ----------*/


void lerEInserirNoPolinomio(POLINOMIO* pol) {
  int numTermos;

  fscanf(entrada, "%d", &numTermos);

  for(int j = 0; j < numTermos; j++) {
    double coeficiente; int expoente;
    fscanf(entrada, "%lf %d", &coeficiente, &expoente);
    inserirTermo(pol, coeficiente, expoente);
  }
}


/*---------- MAIN ----------*/


int main( int argc, char *argv[ ] ) {

  // Leitura dos arquivos de entrada e saida

  if(argc >= 2) {
    entrada = fopen(argv[1], "r");
  }
  if(argc >= 3) {
    saida = fopen(argv[2], "w");
  }



  int cases;
  fscanf(entrada, "%d", &cases);
  fprintf(saida, "%d\n", cases);

  POLINOMIO* polinomio1 = NULL;
  POLINOMIO* polinomio2 = NULL;
  POLINOMIO* resultado = NULL;

  for(int i = 0; i < cases; i++) {
    fscanf(entrada, "%d", &operacao);
    polinomio1 = (POLINOMIO*) malloc(sizeof(POLINOMIO));

    inicializarPolinomio(polinomio1);
    lerEInserirNoPolinomio(polinomio1);


    switch(operacao) {
      case Soma:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = somar(polinomio1, polinomio2);
        fprintf(saida, "%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Subtracao:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = subtrair(polinomio1, polinomio2);
        fprintf(saida, "%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Multiplicacao:
        polinomio2 = (POLINOMIO*) malloc(sizeof(POLINOMIO));
        inicializarPolinomio(polinomio2);
        lerEInserirNoPolinomio(polinomio2);

        resultado = multiplicar(polinomio1, polinomio2);
        fprintf(saida, "%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Derivada:
        resultado = derivar(polinomio1);
        fprintf(saida, "%d\n", operacao);
        imprimirPolinomio(resultado);
        break;
      case Raiz:
        double raiz;
        fscanf(entrada, "%lf", &raiz);

        fprintf(saida, "%d\n", operacao);
        fprintf(saida, "%d\n", verificarRaiz(polinomio1, raiz));
        break;
      case Resolucao:
        double* raizes = calcularRaiz(polinomio1);

        fprintf(saida, "%d\n", operacao);
        fprintf(saida, "%.2lf %.2lf\n", raizes[0], raizes[1]);
        free(raizes);
        break;
      case Impressao:
        fprintf(saida, "%d\n", operacao);
        imprimirPolinomioFormatado(polinomio1);
        break;
      case Grau:
        fprintf(saida, "%d\n", operacao);
        fprintf(saida, "%d\n", grauDoPolinomio(polinomio1));
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

  fclose(entrada);
  fclose(saida);

  return 0;
}

