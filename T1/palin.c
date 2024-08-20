#include <stdio.h>
#include <stdint.h>

#include "palin.h"


int palindrome(uint32_t x) {
    // uint32_t -> int
    // Entrega 1 si la secuencia de 32 bits del entero sin signo x es palíndrome en hexadecimal,
    // es decir que se lee igual de izquierda a derecha como de derecha a izquierda.
    // Entrega 0 si x no es palíndrome.
    //
    // Ejemplos de uso:
    // int rc1 = palindrome(0x3a0ff0a3); // rc1 es 1, es palíndrome
    // int rc2 = palindrome(0x3a0ff0a4); // rc2 es 0, no es palíndrome
    // int rc3 = palindrome(0x3a0fe0b3); // rc3 es 0
    // int rc4 = palindrome(0x11); // rc4 es 0, 0x11 ≡ 0x00000011

    // tamaño en bits de cada cifra del número hexadecimal
    unsigned int bitsize = 4;

    // cadena de comparación 0b1111 = 0xF = 15
    const unsigned int comparison = 0xF;

    // cambio de bits
    unsigned int this_shift;

    // iterar 4 veces
    for (int index = 0; index < 4; index++) {
        // desplazamiento de bits
        this_shift = bitsize * index;
        // encontrar el primer dígito
        uint32_t first = (x >> (28 - this_shift)) & comparison;
        // encontrar el último dígito
        uint32_t last = (x >> this_shift) & comparison;

        // comparar si el primer digito es igual al último
        if (first != last) {
            return 0; // x no es palíndromo
        }
    }

    return 1; // Si llegamos hasta acá, x es palíndromo
}
