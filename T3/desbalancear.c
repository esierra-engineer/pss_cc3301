#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "desbalancear.h"

void desbalancear(Nodo **pa, Nodo **pult) {
    // caso base, el nodo vacío
    if (*pa == NULL) {
        *pult = NULL;
        return;
    }

    // no soy el nodo vacio, copio el puntero de entrada
    Nodo *nodo_actual = *pa;

    // verifico si existe subarbol izquierdo
    Nodo *I = nodo_actual->izq;

    if (I != NULL) {
        /**
         * si existe el subarbol izquierdo hay que desbalancearlo
         * al final el nodo actual deberia quedar a la derecha del ultimo del subarbol izquierdo I */

        // creo una copia del puntero al subarbol izquierdo
        Nodo *I_temp = I;
        // desconecto el puntero al subarbol izquierdo
        nodo_actual->izq = NULL;
        // creo un puntero auxiliar para guardar el ultimo nodo del subarbol izquierdo
        Nodo *pult_aux_I;
        // desbalancear subarbol izquierdo
        desbalancear(&I_temp, &pult_aux_I);
        // el nodo actual queda como hijo derecho del ultimo nodo del subarbol derecho (porque es mayor que todos)
        pult_aux_I->der = nodo_actual;
        // redirigir *pa hacia el subarbol izquierdo que guarde en I_temp
        *pa = I_temp;
    }

    // verifico si existe subarbol derecho
    Nodo *D = nodo_actual->der;

    if (D != NULL) {
        /** si existe el subarbol derecho, desbalancear */
        Nodo *D_temp = D;
        desbalancear(&D_temp, pult);
        nodo_actual->der = D_temp;
    }else {
        /** no tengo subarbol derecho, entonces soy el "último" */
        *pult = nodo_actual;
    }
}

Nodo* copiarArbol(Nodo* a){
    if (a == NULL) {
        return NULL;
    }

    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if (nuevoNodo == NULL) {
        return NULL;
    }

    nuevoNodo->id = a->id;
    nuevoNodo->hash = a->hash;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;

    if (a->izq != NULL) {
        nuevoNodo->izq = copiarArbol(a->izq);
    }
    if (a->der != NULL) {
        nuevoNodo->der = copiarArbol(a->der);
    }

    return nuevoNodo;
}

Nodo *desbalanceado(Nodo *a, Nodo **pult) {
    Nodo* a_copy = copiarArbol(a);

    desbalancear(&a_copy, pult);

    return a_copy;
}
