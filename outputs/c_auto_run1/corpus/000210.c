#include <stdio.h>

#define ARRAY_SIZE 1024

typedef unsigned int uint;

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

uint sumElement(const uint* elem) {
    return (*elem % 2 == 0) ? *elem * 2 : *elem / 2;
}

uint accumulateSum(const ArrayStruct *arr, uint start, uint end) {
    uint sum = 0;
    for (uint i = start; i < end; i++) {
        sum += sumElement(&arr->data[i]);
    }
    return sum;
}

void printAccumulatedSum(const ArrayStruct *arr, uint chunkSize) {
    printf("%u\n", accumulateSum(arr, 0, ARRAY_SIZE));
}

typedef uint (*FuncPtr)(const uint*);

uint doubleAccumulateSum(const ArrayStruct *arr) {
    FuncPtr func = sumElement;
    return func(&arr->data[0]) * 2 + accumulateSum(arr, 0, ARRAY_SIZE - 1);
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printAccumulatedSum(&myArray, ARRAY_SIZE / 2);
    printf("%u\n", doubleAccumulateSum(&myArray));
    return 0;
}