#include "listaLigEstatica.h"

int main() {

  LISTA lista;
  inicializarListaLigadaEstatica(&lista);

  popularLista(&lista, 10);
  printf("Lista Ligada Estatica\n");
  exibirLista(&lista);

  printf("Tamanho: %d\n", tamanhoDaLista(&lista));
  printf("Primeiro Elemento: %d\n", primeiroElemento(&lista));
  printf("Ultimo Elemento: %d\n", ultimoElemento(&lista));
  printf("Quinto Elemento: %d\n", nesimoElemento(&lista, 5));

  destruirLista(&lista);

  return 0;
}
