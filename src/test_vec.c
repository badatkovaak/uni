#include <stdio.h>
#include <stdlib.h>

#define VEC_IMPL
#include "defines.h"
#include "vector.h"

Vec_Impl(u64);

int main(void) {
  printf("%lu", sizeof(unsigned long));
  Vector vec = create_with_capacity_u64(10);
  printf("Hi There %lu %lu %lu\n", (u64)vec.data, (u64)vec.len, vec.capacity);
  for (u64 i = 0; i < 10; i++) {
    push_u64(&vec, i);
  }

  for (u64 i = 0; i < 10; i++) {
    printf("%lu\n", get_u64(&vec, i));
  }
  puts("Hi Mom!");
  return EXIT_SUCCESS;
}
