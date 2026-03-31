#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

// Define a complex struct with nested structures for deeper testing
typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

typedef struct {
    ArrayStruct arr;
    uint multiplier;
} MultipliedArray;

void fillArray(MultipliedArray *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->arr.data[i] = value + i * arr->multiplier;
    }
}

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

void printSum(const MultipliedArray *arr) {
    printf("%u\n", sumArray(&arr->arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint sumWithPointer(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr);
}

int main() {
    MultipliedArray myArray;
    myArray.multiplier = 2;
    fillArray(&myArray, 10);
    printSum(&myArray);
    printf("%u\n", sumWithPointer(&myArray.arr));
    return 0;
}