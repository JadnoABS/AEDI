#include "listaDuplamenteLig.h"


void printarDadosDaLista(LISTA* lista) {
  printf("Lista Duplamente Ligada\n");
  exibirLista(lista);

  printf("Tamanho: %d\n", tamanhoDaLista(lista));
  printf("Primeiro Elemento: %d\n", primeiroElemento(lista));
  printf("Ultimo Elemento: %d\n", ultimoElemento(lista));
  printf("Quinto Elemento: %d\n", enesimoElemento(lista, 5));
}

int main() {

  LISTA lista;
  inicializarListaDuplamenteLigada(&lista);

  popularLista(&lista, 10);

  printarDadosDaLista(&lista);

  int chave;
  printf("Escolha um elemento para remover:\n");
  scanf("%d", &chave);

  excluirElemento(&lista, chave);

  printarDadosDaLista(&lista);

  destruirLista(&lista);

  return 0;
}
