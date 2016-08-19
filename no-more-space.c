#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int size = 1024;
  unsigned char* pointer = NULL;
  long long bytes = 0; // still overflows, but "long long long is too long for GCC"!
  int iterations = 0;

  do {
    pointer = malloc(size);
    bytes += size;
    iterations += 1;

    printf("[%d] allocated %d bytes at 0x%p, %d bytes total\n", iterations, size, (void*)pointer, bytes);
  } while (pointer != NULL);

  // the OS kills the process before we reach this point—why?
  // is there a way to circumvent this?
  printf("allocated %f bytes", bytes);

  return 0;
}
