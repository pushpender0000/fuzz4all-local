#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

// Define a struct to hold an array
typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

// Function to fill the array with incrementing values starting from a given value
void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

// Function to sum the elements of the array with specific operations based on index
uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 3 == 0) { // Complex operation to stress the optimizer
            sum += arr->data[i] * 3;
        } else if (i % 3 == 1) {
            sum += arr->data[i] / 3;
        } else {
            sum += arr->data[i] - i;
        }
    }
    return sum;
}

// Macro to print the result of summing the array, using a function pointer for complexity
#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

typedef uint (*FuncPtr)(const ArrayStruct*); // Define a function pointer type

uint complexSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) + 1000; // Adding a constant value for complexity and stress testing
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 1); // Initialize array with values starting from 1
    PRINT_SUM(&myArray); // Print the sum of the array elements
    printf("%u\n", complexSum(&myArray)); // Use function pointer and add a constant for output
    return 0;
}