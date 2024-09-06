#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "desplazar.h"

void desplazar(char *str, int from, int nbytes, int by) {
  int incremento = 1;
  int current_pos;
  const int len = strlen(str);

  if (by > 0) {
    // muevo el puntero hasta la posicion from + nbytes - 1
    current_pos = (from + nbytes - 1);
    // chequeo estar dentro del string
    if (current_pos >= len) {
      return;
    }
  } else {
    // muevo solo hasta from
    current_pos = from;
    // me desplazo a la derecha
    incremento = -1;
  }

  // desplazo el puntero
  str += current_pos;

  // recorro el string
  int i = nbytes;
  while (i > 0) {
    // veo el destino de esta iteracion
    current_pos += by;
    // si es legal, hacer
    if (current_pos >= 0 && current_pos < len) {
      // guardo lo que haya en esta posicion
      const char this_char = *str;
      // desplazo el puntero
      str += by;
      // escribo
      *str = this_char;
      // me devuelvo y me corro 1 posicion
      str -= (by + incremento);
    }
    else {
      str -= incremento;
    }
    current_pos -= (incremento + by);
    // decremento de 1
    i--;
  }
}

char *desplazamiento(char *str, int from, int nbytes, int by) {
  const int len = strlen(str);

  char *new_str = malloc(len + 1);

  strcpy(new_str, str);

  desplazar(new_str, from, nbytes, by);

  return new_str;
}
