#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[2];
    if (pipe(arr) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        dup2(arr[0], STDIN_FILENO);
        //Не закрито arr[1]
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        close(arr[0]); 
        dprintf(arr[1], "egimfc,w\nwegtee\n");
        close(arr[1]); 
        wait(NULL); 
    }

    return 0;
}
//gcc -Wall 5.c -o 5