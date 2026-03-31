#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

#define COMPUTE_VALUE(x) ((x % 3 == 0) ? (arr->data[x] * 3) : ((x % 3 == 1) ? (arr->data[x] / 3) : (arr->data[x] + 3)))

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        sum += COMPUTE_VALUE(i);
    }
    return sum;
}

void printSum(const ArrayStruct *arr) {
    printf("%u\n", sumArray(arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 2;
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}