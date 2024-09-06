//
// Created by erick on 9/6/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* Retorna una copia de str con las letras convertidas a minúscula, sin editar el string
original
*/
char *lowerCase(char *str);
void to_lower(char *s);

void to_lower(char *s) {
    while (*s != 0) {
        char c = *s;
        if('A' <= c && c <= 'Z') {
            c += 'a' - 'A';
            *s = c;
        }
        s++;
    }
}

char *lowerCase(char *str) {
    int n = strlen(str);
    char *res = malloc(n+1);
    strcpy(res, str);
    to_lower(res);
    return res;
}

void main(){
    char test_str[] = "Hello World";
    char* output = lowerCase(test_str);
    //printf("%s\n", test_str);
    printf("%s\n", output);
}