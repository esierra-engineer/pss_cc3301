#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "test-util.h"
#include "desplazar.h"

// ----------------------------------------------------
// verificar: chequea que str y res sean iguales.  De lo contrario diagnostica
// un resultado incorrecto.

void verificar(char *str, char *ref) {
  if (strcmp(str, ref)==0)
    printf("Test aprobado\n");
  else {
    fprintf(stderr, "resultado incorrecto: \"%s\"\n", str);
    fprintf(stderr, "resultado debio ser: \"%s\"\n", ref);
    fprintf(stderr, "Lo siento, su tarea no aprueba este test\n");
    exit(1);
  }
}

// ----------------------------------------------------
// Resultados correctos de los tests unitarios

char *referencias[ ] = { // str   from   nbytes   by
  "01",                  // "01"    0      1      0
  "00",                  // "01"    0      1      1
  "11",                  // "01"    0      2     -1
  "01",                  // "01"    0      2      0
  "00",                  // "01"    0      2      1
  "11",                  // "01"    1      1     -1
  "01",                  // "01"    1      1      0
  "012",                 // "012"   0      1      0
  "002",                 // "012"   0      1      1
  "010",                 // "012"   0      1      2
  "112",                 // "012"   0      2     -1
  "012",                 // "012"   0      2      0
  "001",                 // "012"   0      2      1
  "010",                 // "012"   0      2      2
  "212",                 // "012"   0      3     -2
  "122",                 // "012"   0      3     -1
  "012",                 // "012"   0      3      0
  "001",                 // "012"   0      3      1
  "010",                 // "012"   0      3      2
  "112",                 // "012"   1      1     -1
  "012",                 // "012"   1      1      0
  "011",                 // "012"   1      1      1
  "212",                 // "012"   1      2     -2
  "122",                 // "012"   1      2     -1
  "012",                 // "012"   1      2      0
  "011",                 // "012"   1      2      1
  "212",                 // "012"   2      1     -2
  "022",                 // "012"   2      1     -1
  "012",                 // "012"   2      1      0
  NULL
};

void test_unitario(void) {
  char *srcs[ ]= {"01", "012"};
  int i= 0;
  for (int j= 0; j<sizeof(srcs)/sizeof(char*); j++) {
    int len= strlen(srcs[j]);
    char *src= srcs[j];
    char dest[len+1];

    for (int from=0; from<len; from++) {
      for (int nbytes= 1; nbytes<=len-from; nbytes++) {
        for (int by= -from-(nbytes-1); by<len-from; by++) {
          strcpy(dest, src);
          desplazar(dest, from, nbytes, by);
          printf("desplazar(\"%s\", %d, %d, %d) entrega \"%s\"\n",
                 src, from, nbytes, by, dest);
          verificar(dest, referencias[i++]);
          // char *des= desplazamiento(dest, from, nbytes, by);
	  // free(des);
        }
      }
    }
  }

  if (referencias[i]!=NULL) {
     fprintf(stderr, "Error en programa de prueba\n");
     exit(1);
  }

  i= 0;
  for (int j= 0; j<sizeof(srcs)/sizeof(char*); j++) {
    int len= strlen(srcs[j]);
    char *src= srcs[j];

    for (int from=0; from<len; from++) {
      for (int nbytes= 1; nbytes<=len-from; nbytes++) {
        for (int by= -from-(nbytes-1); by<len-from; by++) {
          char *dest= desplazamiento(src, from, nbytes, by);
          printf("desplazar(\"%s\", %d, %d, %d) entrega \"%s\"\n",
                 src, from, nbytes, by, dest);
          verificar(dest, referencias[i++]);
	  free(dest);
        }
      }
    }
  }

  if (referencias[i]!=NULL) {
     fprintf(stderr, "Error en programa de prueba\n");
     exit(1);
  }

  printf("Otros tests\n");
  // Este es el string base.  No debe ser modificado.
  char *src= "los 4 puntos cardinales son 3: el norte y el sur";

  // Inicializacion
  int len= strlen(src);
  char dest[len+1];

  // Los 8 tests
  // ----------------------------------------
  printf("1er. test: desplazar \"4 puntos \" en 3 posiciones sin desborde\n");
  strcpy(dest, src);
  desplazar(dest, 4, 9, 3);
  verificar(dest, "los 4 p4 puntos dinales son 3: el norte y el sur");

  // ----------------------------------------
  printf("2do. test: desplazar \"el norte \" en -20 posiciones "
         "sin desborde\n");
  strcpy(dest, src);
  desplazar(dest, 31, 9, -20);
  verificar(dest, "los 4 puntoel norte les son 3: el norte y el sur");

  // ----------------------------------------
  printf("3er. test: desplazar \"norte y\" en 9 posiciones con desborde\n");
  printf("Se pide desplazar 7 caracteres pero solo se pueden desplazar 5\n");
  strcpy(dest, src);
  desplazar(dest, 34, 7, 9);
  verificar(dest, "los 4 puntos cardinales son 3: el norte y enorte");

  // ----------------------------------------
  printf("4to. test: desplazar \"cardinales\" en -17 posiciones "
         "con desborde\n");
  strcpy(dest, src);
  desplazar(dest, 13, 10, -17);
  verificar(dest, "inalespuntos cardinales son 3: el norte y el sur");

  char *res;

  // ----------------------------------------
  printf("5to. test: desplazamiento de \"4 puntos \" en 3 posiciones "
          "sin desborde\n");
  res= desplazamiento(src, 4, 9, 3);
  verificar(res, "los 4 p4 puntos dinales son 3: el norte y el sur");
  free(res);

  // ----------------------------------------
  printf("6to. test: desplazamiento de \"el norte \" en -20 posiciones"
         " sin desborde\n");
  res= desplazamiento(src, 31, 9, -20);
  verificar(res, "los 4 puntoel norte les son 3: el norte y el sur");
  free(res);

  // ----------------------------------------
  printf("7mo. test: desplazamiento de \"norte y\" en 9 posiciones "
         "con desborde\n");
  printf("Se pide desplazar 7 caracteres pero solo se pueden desplazar 5\n");
  res= desplazamiento(src, 34, 7, 9);
  verificar(res, "los 4 puntos cardinales son 3: el norte y enorte");
  free(res);

  // ----------------------------------------
  printf("8vo. test: desplazamiento de \"cardinales\" en -17 posiciones "
         "con desborde\n");
  res= desplazamiento(src, 13, 10, -17);
  verificar(res, "inalespuntos cardinales son 3: el norte y el sur");
  free(res);
}

#ifdef OPT
#define LEN 250
#else
#define LEN 150
#endif

typedef struct {
  char *abc_dest;
  char *abc;
} Param;

static void bench_desplazar(void *ptr) {
  Param *p= ptr;
  char *abc_dest= p->abc_dest;
  char *abc= p->abc;
  for (int from=0; from<LEN; from++) {
    for (int nbytes= 1; nbytes<LEN-from; nbytes++) {
      for (int by= -from-(nbytes-1); by<LEN-from; by++) {
        strcpy(abc_dest, abc);
        desplazar(abc_dest, from, nbytes, by);
        char *des= desplazamiento(abc_dest, from, nbytes, by);
	free(des);
      }
    }
  }
}

void benchmark(int refs[], int n) {
  if (refs!=NULL && n!=1) {
    fprintf(stderr, "El numero de tests debe ser 1\n");
    exit(1);
  }

  char *base= "abcdefghijklmnopqrstuvwxyz0123456789+-!$%&/()=?*{}[],;.:_";
  int len_base= strlen(base);
  char *abc_dest= malloc(LEN+1);
  char *abc= malloc(LEN+1);
  Param p= {abc_dest, abc};

  for (int k= 0; k<LEN; k++) {
    abc[k]= base[k%len_base];
  }
  abc[LEN]= 0;

  //            fun,        ptr,       tiempo_ref,        tolerancia, nintentos
  run_bench(bench_desplazar, &p, refs!=NULL ? refs[0] : -1,       80,    5);

  free(abc_dest);
  free(abc);
}
