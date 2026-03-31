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

#define COMPUTE_VALUE(x, y) ((y % 3 == 0) ? (arr->data[(x * x) / 2] * 3) : ((y % 3 == 1) ? (arr->data[y / 2] / 3) : (arr->data[(x + y) % ARRAY_SIZE] + 3)))

uint sumArray(const ArrayStruct *arr, uint start, uint end) {
    uint sum = 0;
    for (uint i = start; i <= end; i++) {
        sum += COMPUTE_VALUE(i, i);
    }
    return sum;
}

void printSum(const ArrayStruct *arr, uint rangeStart, uint rangeEnd) {
    printf("%u\n", sumArray(arr, rangeStart, rangeEnd));
}

typedef uint (*FuncPtr)(const ArrayStruct*, uint, uint);

uint doubleSum(const ArrayStruct *arr, FuncPtr func, uint start, uint end) {
    return func(arr, start, end) * 2;
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray, 0, ARRAY_SIZE / 2);
    printf("%u\n", doubleSum(&myArray, sumArray, 0, ARRAY_SIZE / 2));
    return 0;
}