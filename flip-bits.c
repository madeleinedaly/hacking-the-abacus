#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ucontext.h>

#define err(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *smalloc(unsigned int size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL) err("got null pointer");
  return ptr;
}

char *getb(FILE *src, size_t len) {
  char *buf;
  buf = (char *)smalloc(2 * sizeof(char) * len + 1);
  for (int i = 0; i < len; i++) sprintf(buf + i * 2, "%02x", fgetc(src));
  return buf;
}

int putb(int mem_fd, unsigned long addr, void *buf, size_t len) {
  lseek(mem_fd, addr, SEEK_SET);
  return write(mem_fd, buf, len);
}

void safe() {
  exit(666);
}

void handler(int cause, siginfo_t *info, void *uap) {
  printf("SIGSEGV raised at %p\n", info->si_addr);
  ucontext_t *context = uap;
  context->uc_mcontext.gregs[14] = (intptr_t)safe; // TODO: determine length of putb invocation
}

int main() {
  int               mem_fd;
  FILE             *urand_fp;
  size_t            bytes_len;
  char             *bytes_buf;
  size_t            addr_len;
  char             *addr_buf;
  unsigned long     addr;
  struct sigaction  sa;

  if ((mem_fd = open("/dev/mem", O_WRONLY)) < 0) err("can't open /dev/mem");
  if ((urand_fp = fopen("/dev/urandom", "r")) == NULL) err("can't open /dev/urandom");

  bytes_len = (size_t)fgetc(urand_fp);
  bytes_buf = getb(urand_fp, bytes_len);

  addr_len = (size_t)sizeof(unsigned long);
  addr_buf = getb(urand_fp, addr_len);
  addr = strtoul(addr_buf, NULL, 16);

  // http://stackoverflow.com/a/3291690
  sa.sa_sigaction = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  if (sigaction(SIGSEGV, &sa, 0)) err("should not occur");

  printf("writing %zu bytes to 0x%lx\n", bytes_len, addr);
  putb(mem_fd, addr, bytes_buf, bytes_len);

  close(mem_fd);
  fclose(urand_fp);

  return EXIT_SUCCESS;
}
