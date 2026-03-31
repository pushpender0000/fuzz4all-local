#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

// Define a union to use in the struct
typedef union {
    uint data[ARRAY_SIZE];
} ArrayUnion;

// Function to fill the array with values based on index
void fillArray(ArrayUnion *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

// Function to sum the elements of the array with specific operations based on index
uint sumArray(const ArrayUnion *arr) {
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

// Function to print the result of summing the array elements
void printSum(const ArrayUnion *arr) {
    printf("%u\n", sumArray(arr));
}

// Define a function pointer type
typedef uint (*FuncPtr)(const ArrayUnion*);

// Function that uses a function pointer and performs an operation on the result of sumArray
uint doubleSum(const ArrayUnion *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 2; // Using function pointer and multiplying result by 2 for complexity
}

int main() {
    ArrayUnion myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}