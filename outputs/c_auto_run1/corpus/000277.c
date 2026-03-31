#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = 50 + i; // Different initial value
    }
}

#define COMPUTE_VALUE(x, y) ((y % 3 == 0) ? (arr->data[x] * 3) : ((y % 3 == 1) ? (arr->data[x] / 3) : (arr->data[x] + 3)))

uint sumArray(const ArrayStruct *arr, uint multiplier) {
    uint totalSum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        totalSum += COMPUTE_VALUE(i, multiplier);
    }
    return totalSum;
}

void printTotalSum(const ArrayStruct *arr) {
    uint sum = sumArray(arr, 1); // Default multiplier for demonstration
    printf("%u\n", sum);
}

typedef uint (*FuncPtr)(const ArrayStruct*, uint);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = (FuncPtr)sumArray;
    return func(arr, 2); // Higher multiplier to ensure different computation in the function
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray);
    printTotalSum(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}