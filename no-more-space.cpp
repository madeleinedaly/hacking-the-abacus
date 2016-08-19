#include <algorithm>
#include <iostream>
#include <cstring>

inline // http://www.cplusplus.com/forum/general/28828/
size_t offset(const char* buf, size_t len, const char* str) {
  return std::search(buf, buf + len, str, str + strlen(str)) - buf;
}

int main() {
  const unsigned long LIMIT = 1996 * 1024 * 1024;
  const int SIZE = 1024;

  const void* start = NULL;
  void* current = NULL;
  unsigned long bytes = 0;

  start = current = malloc(SIZE);
  bytes += SIZE;

  do {
    current = malloc(SIZE);
    bytes += SIZE;

    // std::cout << current << " " << bytes << std::endl;
    if (bytes >= LIMIT) break;
  } while (current != NULL);

  size_t result = offset((const char*)start, bytes, "password");

  if (result < bytes) {
    std::cout << "found string \"password\" at " << result << std::endl;
  } else {
    std::cout << "no string \"password\" found" << std::endl;
  }

  return 0;
}
