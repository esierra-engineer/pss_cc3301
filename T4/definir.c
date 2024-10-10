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
Nodo *leer_nodo(FILE *dicc, char *nom, int desplazamiento) {
    fseek(dicc, desplazamiento, SEEK_CUR);

    NodoArch nodoa;
    fread(&nodoa, sizeof(NodoArch), 1, dicc);

    if (feof(dicc))
        return NULL;

    if (ferror(dicc)) {
        perror(nom);
        exit(1);
    }

    Nodo *pnodo= malloc(sizeof(Nodo));
    pnodo->pos= desplazamiento;
    pnodo->nodoa= nodoa;

    pnodo->llave= malloc(nodoa.tam_llave+1);
    fread(pnodo->llave, nodoa.tam_llave, 1, dicc);
    pnodo->llave[nodoa.tam_llave]= 0;

    pnodo->valor= malloc(nodoa.tam_valor+1);
    fread(pnodo->valor, nodoa.tam_valor, 1, dicc);

    pnodo->valor[nodoa.tam_valor]= 0;

    pnodo->pder = malloc(sizeof(Nodo)+sizeof(NodoArch));
    fread(pnodo->pder, 4, 1, dicc);

    pnodo->pizq = malloc(sizeof(Nodo)+sizeof(NodoArch));
    fread(pnodo->pizq, 4, 1, dicc);

    return pnodo;
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
    char* nom = NULL;
    Nodo* p = leer_nodo(f, nom, 0);

    if (p == NULL) {
        printf("p es null\n");
        free(p);
        return -1;
    }
    printf("llave: %s\n"
           "valor: %s\n", p->llave, p->valor);

    NodoArch nodoa = p->nodoa;

    printf("izq: %d\nder: %d\n", nodoa.izq, nodoa.der);

    free(p);




    // mover el puntero al final
    fseek(f, 0, SEEK_END);

    // posicion inicial del puntero
    int i = 0;

    int32_t buffer;
    int64_t offset;

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