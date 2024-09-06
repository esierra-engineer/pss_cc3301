//
// Created by Erick on 2024-09-01.
//
#include <stdio.h>
#include "desplazar.c"

int compareStrings(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  int output = *(unsigned char *)str1 - *(unsigned char *)str2;

  if (output == 0) {
    return 1;
  }
  return 0;
}

int main(){
  /**
   * test nº 1
   *
   * **/
  printf("Primer Test\n");

  // creo mi string de entrada
  char input[] = "012";
  printf("%s <- input\n", input);

  char output[] = "112";

  desplazar(input, 0, 2,2);

  printf("%s <- input after\n", input);
  printf("%s <- expected input after\n", output);

  //printf("%d\n", compareStrings(input, output));
  printf("----------\n");

  /**
   * test nº 2
   *
   * **/
  printf("Segundo Test\n");
  // creo mi string de entrada
  char input2[] = "abcdefghij";
  printf("%s <- input\n", input2);

  desplazar(input2, 5, 4,-3);

  printf("%s <- input after\n", input2);
  char output2[] = "abfghighij";
  printf("%s <- expected input after\n", output2);

  //printf("%d\n", compareStrings(input2, output2));
  printf("----------\n");

  /**
 * test nº 3
 *
 * **/
  printf("Tercer Test\n");
  // creo mi string de entrada
  char input3[] = "abcdefghij";
  printf("%s <- input\n", input3);
  char output3[] = "abcdefghfg";

  desplazar(input3, 5, 4,3);

  printf("%s <- input after\n", input3);
  printf("%s <- expected input after\n", output3);

  //printf("%d\n", compareStrings(input3, output3));
  printf("----------\n");
}