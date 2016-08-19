#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid;

  do {
    fork();
    pid = getpid();

    printf("forked pid %d\n", pid);
  } while (1);

  return 0;
}
