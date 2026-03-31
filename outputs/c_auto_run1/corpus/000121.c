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

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 2 == 0) {
            sum += arr->data[i] * 2; // Complex operation to stress the optimizer
        } else {
            sum += arr->data[i] / 2; // Another complex operation
        }
    }
    return sum;
}

#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 2; // Using function pointer and multiplying result by 2 for complexity
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    PRINT_SUM(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}