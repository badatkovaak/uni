#include <poll.h>
#include <stdio.h>
#include <unistd.h>

typedef unsigned long un;

int main(void) {
    static const un len = 256;

    FILE* input = stdin;
    // FILE* outputa = stdout;
    struct pollfd fds[1] = {{0, POLLIN, 0}};

    for (;;) {
        char buffer[len] = {0};
        poll(fds, 1, 50000);

        if (fds[0].revents & POLLIN) {
            read(0, buffer, len - 1);
            printf("%s\n", buffer);
        }
    }

    return 0;
}
