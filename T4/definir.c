#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pss.h"
#include "pss.c"

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
    printf("leer_nodo: pos vale: %d\n", pos);
    NodoArch nodoa;
    int rc = fread(&nodoa, sizeof(NodoArch), 1, dicc);
    printf("leer_nodo: fread leyo %d bytes\n", rc);
    printf("el nodoa tiene: \n izq: %d\n der: %d\n, tam_llave: %d\n, tam_valor: %d\n",
        nodoa.izq, nodoa.der, nodoa.tam_llave, nodoa.tam_valor);

    if (feof(dicc))
        return NULL;

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
        exit(1);
    }
    if (nodoa.tam_valor>TAM_MAX || nodoa.tam_valor<0) {
        fprintf(stderr, "El tamanno del valor parece corrupto (%d)\n",
                nodoa.tam_llave);
        exit(1);
    }

    pnodo->llave= malloc(nodoa.tam_llave+1);
    rc= fread(pnodo->llave, nodoa.tam_llave, 1, dicc);
    if (rc<=0) {
        fprintf(stderr, "No se puede leer llave de nodo en posicion %d\n", pos);
        exit(1);
    }
    pnodo->llave[nodoa.tam_llave]= 0;

    pnodo->valor= malloc(nodoa.tam_valor+1);
    rc= fread(pnodo->valor, nodoa.tam_valor, 1, dicc);
    if (rc<=0) {
        fprintf(stderr, "No se puede leer valor de nodo en posicion %d\n", pos);
        exit(1);
    }
    pnodo->valor[nodoa.tam_valor]= 0;
    return pnodo;
}

void freeABB(Nodo* p) {
    free(p->llave);
    free(p->valor);
    free(p);
}


Nodo* buscar_previo(FILE* dicc, char* new_llave, char* new_valor) {
    Nodo* p = leer_nodo(dicc, new_llave);
    // caso base
    if (p == NULL) {
        return NULL;
    }
    // consulto el valor
    char* this_key = p->llave;
    printf("buscar_previo: el valor de this_key: %s\n", this_key);

    // consulto si es igual a la llave buscada
    int string_comp = strcmp(new_llave, this_key);

    if (string_comp == 0) {
        printf("buscar_previo: caso igualdad de llaves\n");
        return p;
    }

    if (string_comp > 0) {
        printf("buscar_previo: entre al caso >0\n");
        int desp_der = (p->nodoa).der;
        printf("buscar_previo: desp_der vale = %d\n", desp_der);
        if (desp_der == -1) {
            return p;
        }
        fseek(dicc, desp_der, SEEK_SET);
        freeABB(p);
        p = buscar_previo(dicc, new_llave, new_valor);
    }
    else {
        int desp_izq = (p->nodoa).izq;
        if (desp_izq == -1) {
            return p;
        }
        fseek(dicc, desp_izq, SEEK_SET);
        freeABB(p);
        p = buscar_previo(dicc, new_llave, new_valor);
    }
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
    int lastpos = ftell(dicc);
    if (p == NULL) {
        return NULL;
    }

    int string_comp = strcmp(new_llave, p->llave);
    printf("buscar_insertar: new_llave = (%s), string_comp = %d\n",
        new_llave, string_comp);

    if (string_comp > 0) {
        int npos = p->pos;

        fseek(dicc, npos, SEEK_SET);
        NodoArch nodoa = p->nodoa;
        nodoa.der = lastpos;
        fwrite(&nodoa, sizeof(NodoArch), 1, dicc);
        p = insertar_nodo(dicc, lastpos, new_llave, new_valor);
    }
    else if (string_comp < 0) {
        int npos = p->pos;
        fseek(dicc, npos, SEEK_SET);
        NodoArch nodoa = p->nodoa;
        nodoa.izq = lastpos;
        fwrite(&nodoa, sizeof(NodoArch), 1, dicc);
        p = insertar_nodo(dicc, lastpos, new_llave, new_valor);
    }
    return p;
}

/* Revise como se implementa la funcion revisar.c
le puede ser de ayuda para realizar la lectura del archivo */

int main(int argc, char **argv) {
    /* Programe aqui su codigo */

    // comprobar la cantidad de parametros recibidos
    if (argc != 4)
    {
        fwrite("uso: ./definir <archivo> <llave> <definicion>\n", 46, 1, stderr);
        exit(1);
    }

    // puntero al archivo
    FILE* f = fopen(argv[1], "rb+");

    // comprobar que el punter no es nulo
    if (f == NULL)
    {
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
        printf("ERROR p es null\n");
        return -1;
    }

    printf("llave: %s -- valor: %s\n", p->llave, p->valor);
    free(p);
    fclose(f);


    // mover el puntero al final
    //fseek(f, 0, SEEK_END);

    // posicion inicial del puntero
    //int i = 0;

    //int32_t buffer;
    //int64_t offset;

    /*// comprobar si el archivo es o no vacio
    if (ftell(f) != 0) {
        do {
            offset = i;

            // muevo el puntero
            fseek(f, offset, SEEK_SET);

            // leo 12 bytes y los guardo en buffer
            fread(&buffer, 12, 1, f);

            int16_t var_3c;
            char* buf_1 = (&new_key_def - (((var_3c + 1) + 0xf) & 0xfffffffffffffff0));
            fread(buf_1, var_3c, 1, f);
            buf_1[var_3c] = 0;

            if (strcmp(buf_1, new_key) == 0)
            {
                fprintf(stderr, "Llave existente: no se puede modificar la llave %s\n", new_key);
                exit(1);
            }*/

            /*i = buffer;
            var_4c_1 = 1;

            if (rax_8 < 0)
            {
                int32_t i_1;
                i = i_1;
                var_4c_1 = 0;
            }
        } while (i != 0xffffffff);*/
    //}


    /**
    * Contar que el numero de argumentos sea al menos 3+1: diccionario-salida llave definicion
    * Guardar la llave nueva en variable char* new_key
    * guardar la nueva definicion en variable char* new_def
    * una variable sin inicializar para guardar el ultimo nodo visitado Nodo* pult
    * abrir el archivo binario en *dicc
        * arrojar error si no se puede abrir
    * Nodo* raiz = leer_nodo(FILE *dicc, char *nom)
    * funcion Nodo* buscar(Nodo* raiz, char* llave, Nodo* pult):
        * if raiz == null:
            * pult = null
            * return
        * leer raiz según estructura dada
        * leer la llave del nodo raiz = char* raiz.llave
        * pult = raiz
        * if raiz.llave = new_key:
            *  return raiz
        * else:
            *  comparar new_key con nodo.key
            *  if new_key < nodo.key:
                *  raiz = raiz.izq
            *  else:
                *  raiz = raiz.der
            *  buscar(raiz, llave, pult)
        * si llegamos hasta acá la llave no existe
        * return null
    * buscar en el diccionario con buscar(raiz, new_key, pult) -> ptr
    * if ptr != null:
        * existe la key, retornar error
    * si no,
    * crear nuevo nodo new_nodo con new_key y new_def
    * comparar new_key con pult->key
    * if new_key > pult->key:
        * pult->der = new_nodo
    * else:
        * pult->izq = new_nodo
    */
}