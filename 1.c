#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    int arr[2];
    if (pipe(arr) == -1) {
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(arr[1], F_GETFL);
    fcntl(arr[1], F_SETFL, flags | O_NONBLOCK);
    char buffer[65536]; // 64 КБ
    memset(buffer, 'A', sizeof(buffer));
    ssize_t count = write(arr[1], buffer, sizeof(buffer));

    if (count == -1) {
        printf("напишіть щосб");
    } else {
        printf("Потрібно було %zu байтів, було введено %zd байтів\n", sizeof(buffer), count);
    }

    close(arr[0]);
    close(arr[1]);
    return 0;
}
//gcc -Wall 1.c -o 1