#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100
#define MAX(a, b) ((a > b) ? a : b)

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

uint sumEvenIndexedElements(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i += 2) { // Increment by 2 to focus on even indices
        if (i % 3 == 0) {
            sum += arr->data[i] * 3; // Complex multiplication with a prime number
        } else if (i % 4 == 0) {
            sum -= arr->data[i] / 2; // Complex division with another prime number
        } else {
            sum += arr->data[i];
        }
    }
    return sum;
}

uint complexFunction(const ArrayStruct *arr, uint (*func)(const ArrayStruct*)) {
    return func(arr);
}

void printSum(const ArrayStruct *arr) {
    printf("%u\n", sumEvenIndexedElements(arr));
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    
    // Using function pointer for a complex operation
    uint (*funcPtr)(const ArrayStruct*) = sumEvenIndexedElements;
    printf("%u\n", complexFunction(&myArray, funcPtr));
    
    return 0;
}