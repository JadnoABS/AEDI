#include "listaLigDinamica.h"


void printarDadosDaLista(LISTA* lista) {
  printf("Lista Ligada Dinamica\n");
  exibirLista(lista);

  printf("Tamanho: %d\n", tamanhoDaLista(lista));
  printf("Primeiro Elemento: %d\n", primeiroElemento(lista));
  printf("Ultimo Elemento: %d\n", ultimoElemento(lista));
  printf("Quinto Elemento: %d\n", enesimoElemento(lista, 5));
}


int main() {

  LISTA lista;
  inicializarListaLigadaDinamica(&lista);

  popularLista(&lista, 10);

  printarDadosDaLista(&lista);

  int chave;

  printf("Escolha um elemento para excluir: \n");
  scanf("%d", &chave);

  excluirElemento(&lista, chave);

  printarDadosDaLista(&lista);

  destruirLista(&lista);

  return 0;
}
