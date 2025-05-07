#include <stdio.h>
#include <unistd.h>

int main() {
  int pid;
  pid = fork();
  printf("%d\n", pid);
}

//gcc -Wall 4.c -o 4