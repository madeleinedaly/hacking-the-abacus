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
#define MAX_BYTES 1024

static void *safe_malloc(unsigned int size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL) {
    handle_error("in safe_malloc(): call to malloc() returned a null pointer");
  }
  return ptr;
}

/*
 * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 * int munmap(void *addr, size_t length);
 *
 * cf. http://linux.die.net/man/2/mmap
 */
int main() {
  // int fd_devmem;
  int fd_logfile;
  FILE *fd_devurandom;
  char *buffer;
  size_t num_bytes;
  size_t i;
  void *addr = NULL;

  // Open /dev/mem for synchronous read-only access
  // if ((fd_devmem = open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
  //     close(fd_devmem);
  //     handle_error("in main() while opening /dev/mem");
  // }

  // Open addr.log for write-/create-/append-only access, with read/write permissions
  if ((fd_logfile = open("addr.log", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)) < 0) {
    close(fd_logfile);
    handle_error("in main() while opening addr.log");
  }

  // Open /dev/urandom for read-only access
  if ((fd_devurandom = fopen("/dev/urandom", "r")) == NULL) {
    handle_error("in main() while opening /dev/urandom");
  }

  // Get a random number of bytes from /dev/urandom
  num_bytes = (size_t) fgetc(fd_devurandom);
  buffer = (char *) safe_malloc(2 * sizeof(char) * num_bytes + 1);
  for (i = 0; i < num_bytes; i++) {
    sprintf(buffer + i * 2, "%02x", fgetc(fd_devurandom));
  }
  fclose(fd_devurandom);
  printf("[debug] %zu bytes @ %p: %s\n", num_bytes, buffer, buffer);

  // Log the buffer's address
  addr = &buffer;
  strncat(addr, "\n", 1);
  // TODO: format into hexadecimal values
  write(fd_logfile, addr, 4);

  printf("[debug] addr: %lu\n", (unsigned long)addr);

  // TODO: Get a random memory address by taking some bytes from /dev/urandom

  // TODO: Write buffer to that address in /dev/mem
  // addr = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd_devmem, __TODO_offset__);

  // if (addr == MAP_FAILED) {
  //     handle_error("in main(): writing to /dev/mem failed");
  // } else {
  //     printf("[debug] wrote %d random bytes to %p", num_bytes, buffer);
  //     write(fd_logfile, buffer, sizeof(buffer));
  // }

  // if (munmap(addr, MAPPED_SIZE) == -1) {
  //     handle_error("in main(): call to munmap() failed");
  // }

  // close(fd_devmem);

  // TODO: Catch SIGSEGV (which might get thrown when trying to write to read-
  //       only memory) as well as any other errors, and keep track of them.

  return 0;
}
