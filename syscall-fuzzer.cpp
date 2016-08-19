// g++ -std=c++1 -Wall -g -o syscall-fuzzer syscall-fuzzer.cpp && ./syscall-fuzzer
#include <algorithm>
#include <iostream>
#include <random>
// #include <map>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

const int not_impl[] = {174, 177, 178, 180, 181, 182, 183, 184, 185, 214, 215, 236};


int main() {
  int sysno;
  bool not_allowed;

  // // TODO: map sysnos to default args
  // int[] sysnos = {};
  // for (int i = 0; i <= 300; i++) {
  //   not_allowed = std::any_of(std::begin(not_impl), std::end(not_impl), [&](int i) {
  //       return i == sysno;
  //     });

  //   if (not_allowed) {
  //     continue;
  //   } else {
  //     sysnos[i] = i;
  //   }
  // }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 300);

  for (int i = 0; i < 100; i++) {
    do {
      sysno = dis(gen);

      not_allowed = std::any_of(std::begin(not_impl), std::end(not_impl), [&](int i) {
          return i == sysno;
        });
    } while (not_allowed);

    std::cout << sysno << ' ';
  }
  std::cout << std::endl;

  return 0;
}
