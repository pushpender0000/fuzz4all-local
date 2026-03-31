#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100
#define PRINT_RESULT(x) printf("%u\n", x)

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

uint sumArray(const ArrayStruct *arr) {
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

uint multiplySum(const ArrayStruct *arr) {
    uint mul = 1;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 2 == 0) {
            mul *= arr->data[i]; // Complex operation to stress the optimizer
        } else {
            mul /= arr->data[i]; // Another complex operation
        }
    }
    return mul;
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 2 + multiplySum(arr); // Using function pointer and multiplying result by 2 for complexity
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, rand()); // Seed random number generator for different input each time
    PRINT_RESULT(doubleSum(&myArray));
    return 0;
}