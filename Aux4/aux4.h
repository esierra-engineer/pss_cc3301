//
// Created by erick on 8/30/24.
//

#ifndef AUX4_H
#define AUX4_H

#endif //AUX4_H
typedef struct nodo {
    int x;
    struct nodo *sgte;
} Nodo;
void append(Nodo **pa, Nodo *b);