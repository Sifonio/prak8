#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    unsigned char buffer[4];
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    fd = open("2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    write(fd, data, sizeof(data));
    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);

    for (int i = 0; i < 4; i++) {
        printf("%u ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}

//gcc -Wall 2.c -o 2