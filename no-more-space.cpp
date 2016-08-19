#include <algorithm>
#include <iostream>
#include <cstring>

// http://www.cplusplus.com/forum/general/28828/
inline size_t offset(const char* buf, size_t len, const char* str) {
  return std::search(buf, buf + len, str, str + strlen(str)) - buf;
}

int main() {
  const unsigned long LIMIT = 1996 * 1024 * 1024;
  const int SIZE = 1024;

  void* current = NULL;
  unsigned long bytes = 0;

  const void* start = current = malloc(SIZE);
  bytes += SIZE;

  do {
    current = malloc(SIZE);
    bytes += SIZE;

    if (bytes >= LIMIT) break;
  } while (current != NULL);

  const size_t result = offset((const char*)start, bytes, "password");

  if (result < bytes) {
    std::cout << "found string \"password\" at offset " << result << std::endl;
  } else {
    std::cout << "no string \"password\" found" << std::endl;
  }

  return 0;
}
