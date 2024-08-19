#include <stdio.h>
#include <stdint.h>

#include "palin.h"

int palindrome(uint32_t x) {
  printf("entrada: %x\n", x);

   // int i = 0;
   // while (i <= 28) {
   //   printf("LEFT i = %d: %x\n",i, x<<i);
   //   i = i + 4;
   // }
  //
  // int j = 0;
  // while (j <= 28) {
  //   printf("RIGHT j = %d: %x\n",i, x>>j);
  //   j = j + 4;
  // }

  // el ultimo se obtiene con x<<28 (28 = 7 * 4)
  // el primero se obtiene con x>>28 (28 = 7 * 4)

  uint32_t first = x >> 28;
  uint32_t last = x << 28;

  printf("First: %x\n", first);
  printf("Last: %x\n", last >> 28);

  return 0;
}
