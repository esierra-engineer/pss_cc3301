//
// Created by erick on 8/30/24.
//
#include <stdio.h>

typedef struct nodo {
    int x;
    struct nodo *izq, *der;
} Nodo;

void podar(Nodo **pa, int y){
  Nodo *a = *pa;
  if(a == NULL){
    return;
  }

  if(a -> x > y){
      podar(&a -> izq, y);
      *pa = a -> izq;
    }
  else {
      podar(&a -> der, y);
  }
}

void main(){}