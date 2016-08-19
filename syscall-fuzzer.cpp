#include <map>
#include <iterator>
// #include <string>

#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>

int rand_syscall() {
  int sysno;
  int not_implemented[] = {174, 177, 178, 180, 181, 182, 183, 184, 185, 214, 215, 236};
  auto start = std::begin(not_implemented);
  auto end = std::end(not_implemented);

  do {
    sysno = rand() % 301;
  } while (std::any_of(start, end, sysno));

  return sysno;
}

int main() {
  int sysno;
  int i;

  for (i = 0; i < 100; i++) {
    sysno = rand_syscall();

    printf("%d\n", sysno);
  }

  return 0;
}
