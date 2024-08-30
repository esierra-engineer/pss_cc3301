//
// Created by erick on 8/30/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "aux4.h"

void append(Nodo **pa, Nodo *b) {
    if(*pa == NULL) {
        *pa = b;
    }
    else {
        append(&(*pa) -> sgte, b);
    }
    return;
}