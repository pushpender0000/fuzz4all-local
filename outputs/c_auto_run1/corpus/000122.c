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

#define OPERATION(x) ((x % 2 == 0) ? (x * 2) : (x / 2))

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        sum += OPERATION(arr->data[i]);
    }
    return sum;
}

void printSum(const ArrayStruct *arr) {
    printf("%u\n", sumArray(arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint complexSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 3; // Adding more complexity by multiplying the result by 3
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    printf("%u\n", complexSum(&myArray));
    return 0;
}