#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TAM_MAX 255

typedef struct {
    int izq, der;
    short tam_llave, tam_valor;
} NodoArch;

typedef struct nodo {
    intptr_t pos;
    char *llave, *valor;
    struct nodo *pizq, *pder;
    NodoArch nodoa;
} Nodo;


// Lee un nodo en el diccionario en dicc
Nodo *leer_nodo(FILE *dicc, char *nom) {
    int pos= ftell(dicc);
    NodoArch nodoa;
    int rc = fread(&nodoa, sizeof(NodoArch), 1, dicc);

    if (feof(dicc)) {
        return NULL;
    }

    if (ferror(dicc)) {
        perror(nom);
        exit(1);
    }

    Nodo *pnodo= malloc(sizeof(Nodo));
    pnodo->pos= pos;
    pnodo->nodoa= nodoa;
    if (nodoa.tam_llave>TAM_MAX || nodoa.tam_llave<0) {
        fprintf(stderr, "El tamanno de la llave parece corrupto (%d)\n",
                nodoa.tam_llave);
        free(pnodo);
        exit(1);
    }
    if (nodoa.tam_valor>TAM_MAX || nodoa.tam_valor<0) {
        fprintf(stderr, "El tamanno del valor parece corrupto (%d)\n",
                nodoa.tam_llave);
        free(pnodo);
        exit(1);
    }

    pnodo->llave= malloc(nodoa.tam_llave+1);
    rc= fread(pnodo->llave, nodoa.tam_llave, 1, dicc);
    if (rc<=0) {
        fprintf(stderr, "No se puede leer llave de nodo en posicion %d\n", pos);
        free(pnodo->llave);
        free(pnodo);
        exit(1);
    }
    pnodo->llave[nodoa.tam_llave]= 0;

    pnodo->valor= malloc(nodoa.tam_valor+1);
    rc= fread(pnodo->valor, nodoa.tam_valor, 1, dicc);
    if (rc<=0) {
        fprintf(stderr, "No se puede leer valor de nodo en posicion %d\n", pos);
        free(pnodo->llave);
        free(pnodo->valor);
        free(pnodo);
        exit(1);
    }
    pnodo->valor[nodoa.tam_valor]= 0;
    return pnodo;
}

void freeABB(Nodo* p) {
    if (p != NULL) {
        free(p->llave);
        free(p->valor);
        free(p);
    }
}

Nodo* buscar_previo(FILE* dicc, char* new_llave, char* new_valor) {
    Nodo* p = leer_nodo(dicc, new_llave);
    // caso base
    if (p == NULL) {
        return NULL;
    }
    // consulto el valor
    char* this_key = p->llave;

    // consulto si es igual a la llave buscada
    int string_comp = strcmp(new_llave, this_key);

    int desp;
    if (string_comp > 0) {
        desp = (p->nodoa).der;
        if (desp == -1) {
            return p;
        }
    }
    else {
        desp = (p->nodoa).izq;
        if (desp == -1) {
            return p;
        }
    }
    fseek(dicc, desp, SEEK_SET);
    freeABB(p);
    p = buscar_previo(dicc, new_llave, new_valor);
    return p;
}

Nodo* insertar_nodo(FILE* dicc, int lastpos, char* new_llave, char* new_valor) {
    fseek(dicc, 0, SEEK_END);
    NodoArch nodoa;
    nodoa.izq = -1;
    nodoa.der = -1;
    nodoa.tam_llave = strlen(new_llave);
    nodoa.tam_valor = strlen(new_valor);

    fwrite(&nodoa, sizeof(NodoArch), 1, dicc);

    if (ferror(dicc)) {
        return NULL;
    }

    Nodo *pnodo= malloc(sizeof(Nodo));
    pnodo->pos= lastpos;
    pnodo->nodoa= nodoa;
    pnodo->llave= new_llave;
    pnodo->valor= new_valor;

    fwrite(new_llave, nodoa.tam_llave, 1, dicc);
    fwrite(new_valor, nodoa.tam_valor, 1, dicc);
    return pnodo;
}

Nodo* buscar_insertar(FILE* dicc, char* new_llave, char* new_valor) {
    Nodo* p = buscar_previo(dicc, new_llave, new_valor);
    fseek(dicc, 0, SEEK_END);
    int lastpos = ftell(dicc);
    if (p == NULL) {
        p = insertar_nodo(dicc, lastpos, new_llave, new_valor);
        return p;
    }

    int string_comp = strcmp(new_llave, p->llave);

    if (string_comp == 0) {
        fprintf(stderr, "Llave existente: no se puede modificar la llave %s\n", new_llave);
        exit(1);
    }

    NodoArch nodoa = p->nodoa;
    int npos = p->pos;
    fseek(dicc, npos, SEEK_SET);

    if (string_comp > 0) {
        nodoa.der = lastpos;
    }
    else {
        nodoa.izq = lastpos;
    }

    fwrite(&nodoa, sizeof(NodoArch), 1, dicc);
    freeABB(p);
    p = insertar_nodo(dicc, lastpos, new_llave, new_valor);
    return p;
}

/* Revise como se implementa la funcion revisar.c
le puede ser de ayuda para realizar la lectura del archivo */

int main(int argc, char **argv) {
    /* Programe aqui su codigo */

    // comprobar la cantidad de parametros recibidos
    if (argc != 4){
        fprintf(stderr, "uso: ./definir <archivo> <llave> <definicion>\n");
        exit(1);
    }

    // puntero al archivo
    FILE* f = fopen(argv[1], "rb+");

    // comprobar que el puntero no es nulo
    if (f == NULL){
        perror(argv[1]);
        exit(1);
    }

    // la nueva llave
    char* new_key = argv[2];

    // la definicion de la nueva llave
    char* new_key_def = argv[3];

    // testing zone
    Nodo* p = buscar_insertar(f, new_key, new_key_def);
    if (p == NULL) {
        fclose(f);
        return -1;
    }

    free(p);
    fclose(f);

    return 0;
}