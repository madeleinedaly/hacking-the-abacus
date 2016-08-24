#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void *smalloc(unsigned int size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL) {
    handle_error("got null pointer");
  }
  return ptr;
}

static char *getb(FILE *src, size_t len) {
  char *buf;
  buf = (char *)smalloc(2 * sizeof(char) * len + 1);
  for (int i = 0; i < len; i++) {
    sprintf(buf + i * 2, "%02x", fgetc(src));
  }
  return buf;
}

int main() {
  FILE           *urand;
  FILE           *log;
  size_t          bytes_len;
  char           *bytes_buf;
  size_t          addr_len;
  char           *addr_buf;
  unsigned long   addr;

  if ((urand = fopen("/dev/urandom", "r")) == NULL) {
    handle_error("can't open /dev/urandom");
  }

  if ((log = fopen("addr.log", "a")) == NULL) {
    handle_error("can't open addr.log");
  }


  // get random number of random bytes
  bytes_len = (size_t)fgetc(urand);
  bytes_buf = getb(urand, bytes_len);

  printf("\ngot %zu random bytes:\n%s\n", bytes_len, bytes_buf);


  // get random address
  addr_len = (size_t)sizeof(unsigned long);
  addr_buf = getb(urand, addr_len);
  addr = strtoul(addr_buf, NULL, 16);

  printf("addr: 0x%lx\n", addr);


  fclose(urand);
  fclose(log);

  return EXIT_SUCCESS;
}
