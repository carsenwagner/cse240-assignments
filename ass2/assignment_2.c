#include <stdio.h>
#include <stdint.h>

int main() {
  printf("sizeof(char) %lu\n", sizeof(char));
  printf("sizeof(short) %lu\n", sizeof(short));
  printf("sizeof(int) %lu\n", sizeof(int));
  printf("sizeof(long) = %lu\n", sizeof(long));
  printf("sizeof(long long) = %lu\n", sizeof(long long));
  printf("sizeof(float) = %lu\n", sizeof(float));
  printf("sizeof(double) = %lu\n", sizeof(double));
  printf("sizeof(long double) = %lu\n", sizeof(long double));
  printf("sizeof(int32_t) = %lu\n", sizeof(int32_t));
  printf("sizeof(int64_t) = %lu\n", sizeof(int64_t));
}
