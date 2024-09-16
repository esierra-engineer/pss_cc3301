#include <stdio.h>
#include "tools.c"


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

    Nodo* nuevoNodo = malloc(sizeof(Nodo));
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
    if (a == NULL) {
        printf("null\n");
        return a;
    }

    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if (nuevoNodo == NULL) {
        printf("malloc tuvo un problema\n");
        return NULL;
    }

    nuevoNodo->id = a->id;
    nuevoNodo->hash = a->hash;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;

    nuevoNodo = a;

    desbalancear(&nuevoNodo, pult);

    return nuevoNodo;
}


void main() {
    // Ejemplo de uso
    /*Nodo n5 = {11, 3, NULL, NULL};
    Nodo n4 = {2, 4, NULL, NULL};
    Nodo n3 = {5, 4, NULL, NULL};
    Nodo n2 = {4, 4, &n4, &n3};
    Nodo n1 = {10, 3, NULL, &n5};
    Nodo raiz = {8, 5, &n2, &n1};

    Nodo* ult = NULL;
    Nodo* arbol = &raiz;

    printf("Árbol de entrada:\n");
    treeprint(arbol);

    printf("\n");

    printf("Arbol desbalanceado con desbalancear:\n");
    desbalancear(&arbol, &ult);
    treeprint(arbol);

    printf("\n");

    printf("Ultimo Nodo: %d\n\n\n\n\n\n", ult->id);*/

    /*Nodo n52 = {11, 3, NULL, NULL};
    Nodo n42 = {2, 4, NULL, NULL};
    Nodo n32 = {5, 4, NULL, NULL};
    Nodo n22 = {4, 4, &n42, &n32};
    Nodo n12 = {10, 3, NULL, &n52};
    Nodo raiz2 = {8, 5, &n22, &n12};

    Nodo* ult2 = NULL;
    Nodo* arbol2 = &raiz2;

    printf("Árbol de entrada 2:\n");
    treeprint(arbol2);

    printf("Arbol desbalanceado 2:\n");
    Nodo* arbol3 = desbalanceado(arbol2, &ult2);
    treeprint(arbol3);

    printf("Árbol de entrada 2 despues de aplicar desbalanceado:\n");
    treeprint(arbol2);*/

    // El arbol binario del enunciado

    /*
    static Nodo nu= { 'u', 0, NULL, NULL };
    static Nodo ns= { 's', 0, NULL, &nu };
    static Nodo nw= { 'w', 0, NULL, NULL };
    static Nodo nx= { 'x', 0, &nw, NULL };
    static Nodo nv= { 'v', 0, &ns, &nx };

    treeprint(&nv);

    Nodo* ult = NULL;
    Nodo* arbol = &nv;

    desbalancear(&arbol, &ult);

    treeprint(arbol);
    printf("Ultimo Nodo: %d\n\n\n\n\n\n", ult->id);*/
    // static Nodo nu= { 'u', 0, NULL, NULL };
    // static Nodo ns= { 's', 0, NULL, &nu };
    // static Nodo nw= { 'w', 0, NULL, NULL };
    // static Nodo nx= { 'x', 0, &nw, NULL };
    // static Nodo nv;

    Nodo* ult = NULL;
    Nodo* arbol = NULL;

    printf("Árbol de entrada 2 antes de aplicar desbalanceado:\n");
    treeprint(arbol);
    printf("%d\n", &arbol);

    printf("Arbol desbalanceado 2:\n");
    Nodo* arbol3 = desbalanceado(arbol, &ult);
    treeprint(arbol3);
    printf("%d\n", &arbol3);

    printf("Árbol de entrada 2 despues de aplicar desbalanceado:\n");
    treeprint(arbol);
    printf("%d\n", &arbol);
}
