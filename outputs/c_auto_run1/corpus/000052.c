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
            sum += arr->data[i] * 2; // Complex multiplication and addition
        } else {
            sum += arr->data[i] / 3; // Complex division
        }
    }
    return sum;
}

void printSum(const ArrayStruct *arr) {
    printf("%u\n", sumArray(arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint complexFunction(const ArrayStruct *arr, FuncPtr func) {
    return func(arr);
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    
    // Using function pointer for a complex operation
    printf("%u\n", complexFunction(&myArray, sumArray));
    
    return 0;
}