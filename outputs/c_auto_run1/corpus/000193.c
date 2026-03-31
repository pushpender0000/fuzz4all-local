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

#define COMPUTE_VALUE(x, y) ((y % 3 == 0) ? (arr->data[y] * 3) : ((y % 3 == 1) ? (arr->data[y] / 3) : (arr->data[y] + 3)))

uint sumArray(const ArrayStruct *arr, uint offset) {
    uint sum = 0;
    for (uint i = offset; i < ARRAY_SIZE; i++) {
        sum += COMPUTE_VALUE(i, sum);
    }
    return sum;
}

void printSum(const ArrayStruct *arr, uint start) {
    printf("%u\n", sumArray(arr, start));
}

typedef uint (*FuncPtr)(const ArrayStruct*, uint);

uint doubleSum(const ArrayStruct *arr, FuncPtr func, uint shift) {
    return func(arr, 0) * 2 + shift;
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray, 5);
    printf("%u\n", doubleSum(&myArray, sumArray, 10));
    return 0;
}