#include <algorithm>
#include <iostream>
#include <random>
// #include <map>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
// #include <signal.h>
// #include <stdio.h>

void invoke(int sysno, int fd) {
    const int size = 5;
    char buf[size];

    switch (sysno) {

    case SYS_read: // (unsigned int fd,	char __user * buf, size_t count)
        syscall(SYS_read, fd, buf, size);
        printf("%s\n", buf);
        break;

    case SYS_write: // (unsigned int fd, const char __user * buf, size_t count)
        syscall(SYS_write, fd, "boo!\n", size);
        break;

    case SYS_open: // (const char __user * filename, int flags, umode_t mode)
        break;

    case SYS_close: break;
    case SYS_stat: break;
    case SYS_fstat: break;
    case SYS_lstat: break;
    case SYS_poll: break;
    default: break;
    }
}

// non-implemented system call numbers
const int skip[] = {174, 177, 178, 180, 181, 182, 183, 184, 185, 214, 215, 236};
auto start = std::begin(skip);
auto end = std::end(skip);

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 313);

    int fd = open("./file.txt", O_RDWR | O_APPEND);
    int sysno;

    for (int i = 0; i < 100; i++) {
        do {
            sysno = dis(gen);
        } while (std::any_of(start, end, [&](int j) { return j == sysno; }));

        // FIXME: this should happen in a child process
        invoke(sysno, fd);
    }

    close(fd);
    return 0;
}
