#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>

#include "test-util.h"

#define TAM 10
#define NTESTS 1000

void test_unitario(void) {
  // Ignorar
  // Se hace con un script de bash
}

typedef struct {
  char *definir_bin, *dicc_nom;
  FILE *dicc;
  int llaves;
  char exists[NTESTS];
} Param;

static void init_definir(void *ptr) {
  Param *p= ptr;
  p->definir_bin= getenv("DEFINIR_BIN");
  if (p->definir_bin==NULL)
    p->definir_bin= "./definir.bin";

  // Create empty bench_dcc.bin
  p->dicc_nom= "bench_dicc.bin";
  FILE *dicc= fopen(p->dicc_nom, "w");
  if (dicc==NULL) {
    perror(p->dicc_nom);
    exit(1);
  }
  fclose(dicc);

  p->llaves= 0;
  for (int i= 0; i<NTESTS; i++)
    p->exists[i]= 0;
}

static void clean_definir(void *ptr) {
  Param *p= ptr;
  printf("Se agregaron %d llaves\n", p->llaves);
}

static void bench_definir(void *ptr) {
  Param *p= ptr;
  srandom(100);
  for (int i= 0; i<NTESTS; i++) {
    int k= random()%NTESTS;
    if (!p->exists[k]) {
      p->exists[k]= 1;
      p->llaves++;
      char llave[20];
      sprintf(llave, "%d", k);
      int pid= fork();
      if (pid==0) {
        execl(p->definir_bin, p->definir_bin, p->dicc_nom, llave, llave, NULL);
        perror(p->definir_bin);
        exit(19);
      }
      else {
        int status= 0;
        waitpid(pid, &status, 0);
        int rc= WEXITSTATUS(status);
        if (rc != 0) {
          fprintf(stderr, "Codigo de retorno %d es incorrecto con llave %d\n",
                          rc, k);
          exit(1);
        }
      }
    }
  }
}

void benchmark(int refs[], int n) {
  Param *p= malloc(sizeof(Param));
  printf("\n");
  printf("====================\n");
  printf("Benchmark de definir\n");
  printf("====================\n");
  //        prologo        benchmark       clean up
  run_bench(init_definir, bench_definir, clean_definir,
  //        ptr, tiempo_ref,    tolerancia, nintentos
            p ,   refs[0]  ,        80    ,    5 );
  free(p);
}
