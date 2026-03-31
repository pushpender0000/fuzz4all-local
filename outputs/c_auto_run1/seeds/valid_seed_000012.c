#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void initializeArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

uint calculateSum(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 3 == 0) {
            sum += arr->data[i] * 3; // Complex operation to stress the optimizer
        } else if (i % 3 == 1) {
            sum += arr->data[i] / 3; // Another complex operation
        } else {
            sum += arr->data[i] + 3; // Yet another complex operation
        }
    }
    return sum;
}

void printResult(const ArrayStruct *arr) {
    printf("%u\n", calculateSum(arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleTheSum(const ArrayStruct *arr) {
    FuncPtr func = calculateSum;
    return func(arr) * 2; // Using function pointer and multiplying result by 2 for complexity
}

int main() {
    ArrayStruct myArray;
    initializeArray(&myArray, 10);
    printResult(&myArray);
    printf("%u\n", doubleTheSum(&myArray));
    return 0;
}