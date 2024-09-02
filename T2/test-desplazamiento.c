//
// Created by Erick on 2024-09-02.
//
#include <stdio.h>
#include "desplazar.c"


int main() {
    /**
     * test nº 1
     *
     * **/
    printf("Primer Test\n");

    // creo mi string de entrada
    char input[] = "abcdefghij";
    printf("%s <- input\n", input);

    char expected_output[] = "abcdcdehij";

    char *output = desplazamiento(input, 2, 3,2);

    printf("%s <- input after\n", input);
    printf("%s <- output after\n", output);
    printf("%s <- expected input after\n", expected_output);

    //printf("%d\n", compareStrings(input, output));
    printf("----------\n");
}