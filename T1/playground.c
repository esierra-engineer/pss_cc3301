//
// Created by esierra on 8/19/24.
//
#include <stdio.h>
#include <string.h> // en este headers estan las principales funciones para trabajar con strings

int palindromo(char* s);

int main() {
  // tests
  char test1[] = "anitalavalatina"; // es palindromo
  char test2[] = "abcba"; // es palindromo
  char test3[] = "abc"; // no es palindromo

  printf("test1: %d\n", palindromo(test1));
  printf("test2: %d\n", palindromo(test2));
  printf("test3: %d\n", palindromo(test3));
}

int palindromo(char* s) {
  char* final = s + strlen(s) - 1; // usamos strlen para obtener el largo del string y con eso podemos obtener un puntero al ultimo caracter
  while(s < final) { // mientras no nos pasemos del medio del string
    if(*s != *final) // si los caracteres son distintos, no es palindromo
      return 0;
    s++;
    final--;
  }
  return 1; // si llegamos hasta aca, es palindromo
}