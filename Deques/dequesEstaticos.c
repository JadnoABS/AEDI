#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

#define NUMERO_INVALIDO -1

typedef int TIPOCHAVE;


typedef struct no {
  TIPOCHAVE chave;
} NO; 


typedef struct {
  NO A[MAX];
  int inicio1;
  int inicio2;
} DEQUE;


void inicializarDeque(DEQUE* deque) {
  deque->inicio1 = -1;
  deque->inicio2 = -1;
};

int tamanhoDoDeque(DEQUE deque) {
  if(deque->inicio1 < 0) return 0;

  int tamanho;
  if(deque->inicio1 <= deque->inicio2) {
    tamanho = deque->inicio2 - deque->inicio1 + 1;
  } else {
    tamanho = MAX - d->inicio1 + d->inicio2 + 1;
  }

  return tamanho;
};

bool entrarDeque1(TIPOCHAVE ch, DEQUE* deque) {
  if(tamanhoDoDeque(*deque) >= MAX) return false;

  if(deque->inicio1 < 0) { deque->inicio1 = deque->inicio2 = 0; }
  if(deque->inicio1 > 0){
    deque->inicio1--;
  } else {
    deque->inicio1 = MAX-1;
  }
  deque->A[deque->inicio1].chave = ch;

  return true;
};

TIPOCHAVE sairDeque1(DEQUE* deque) {
  if(deque->inicio1 < 0) return -1;

  TIPOCHAVE ch = deque->A[deque->inicio1].chave;
  if(deque->inicio1 != deque->inicio2){
    deque->inicio1 = (deque->inicio1 + 1) % MAX;
  } else {
    deque->inicio1 = deque->inicio2 = -1;
  }

  return ch;
};

void destruirDeque(DEQUE* deque) {
  deque->inicio1 = -1;
  deque->inicio1 = -1;
};












