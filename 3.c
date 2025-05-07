#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare_int(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int is_sorted(int *arr, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

void generate_sorted(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = i;
}

void generate_reverse(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = size - i;
}

void generate_constant(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = 42;
}

void generate_random(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = rand();
}

// Поганий для qsort масив в якому чергуються маленькі та великі числа
void generate_bad(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = (i % 2 == 0) ? 0 : size;
    }
}

void run_test(const char *name, void (*generator)(int*, size_t), size_t size) {
    int *arr = malloc(size * sizeof(int));
    generator(arr, size);

    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare_int);
    clock_t end = clock();

    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("Тест: %s, Розмір: %zu, Час: %.3f ms, %s\n", name, size, elapsed_ms, is_sorted(arr, size) ? "відсортований коректно" : "відсортований некоректно");
    free(arr);
}

int main() {
    srand(time(NULL));

    size_t sizes[] = {1000, 10000, 50000, 100000};

    void (*generators[])(int*, size_t) = {
        generate_sorted,
        generate_reverse,
        generate_constant,
        generate_random,
        generate_bad
    };

    const char *names[] = {
        "Відсортований",
        "Відсортований навпаки",
        "Константний",
        "Рандомний",
        "Поганий"
    };

    for (size_t s = 0; s < sizeof(sizes)/sizeof(sizes[0]); s++) {
        printf("\nРозмір масиву: %zu\n", sizes[s]);
        for (int t = 0; t < 5; t++) {
            run_test(names[t], generators[t], sizes[s]);
        }
    }

    return 0;
}
//gcc -Wall 3.c -o 3