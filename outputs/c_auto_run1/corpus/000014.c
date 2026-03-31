#include <stdio.h>

#define ARRAY_SIZE 1024
#define MAX(a, b) ((a > b) ? a : b)

typedef struct {
    int data[ARRAY_SIZE];
} LargeArray;

void fillArray(LargeArray *arr) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = i + 1;
    }
}

typedef int (*MathFunc)(const LargeArray *);

int sumArrayDirectly(const LargeArray *arr) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

void printSumWithCallback(const LargeArray *arr, MathFunc callback) {
    printf("%d\n", callback(arr));
}

int main() {
    LargeArray myArray;
    fillArray(&myArray);

    // Using a function pointer to call the sum function directly
    int (*sumPtr)(const LargeArray *) = sumArrayDirectly;
    printSumWithCallback(&myArray, sumPtr);

    return 0;
}