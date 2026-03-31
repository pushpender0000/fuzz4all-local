#include <stdio.h>

// Define a macro for array size
#define ARRAY_SIZE 1024

// Typedef for unsigned int
typedef unsigned int uint;

// Define a struct with an array of uints
typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

// Macro to fill the array with increasing values multiplied by a factor
#define FILL_FACTOR 3
void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i * FILL_FACTOR;
    }
}

// Function to sum the array elements with complex operations
uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 2 == 0) {
            sum += arr->data[i] * arr->data[i]; // Square the value
        } else {
            sum += arr->data[i] / (i + 1);     // Divide by increasing values
        }
    }
    return sum;
}

// Function to print the sum of the array using a function pointer
void printSum(const ArrayStruct *arr) {
    printf("%u\n", sumArray(arr));
}

// Typedef for function pointer type that takes an ArrayStruct* and returns uint
typedef uint (*FuncPtr)(const ArrayStruct*);

// Function demonstrating the use of a function pointer
uint complexFunction(const ArrayStruct *arr, FuncPtr func) {
    return func(arr);
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10); // Fill array with initial value plus increasing values multiplied by FILL_FACTOR
    printSum(&myArray);      // Print the sum of the array elements
    
    // Use function pointer for a complex operation
    printf("%u\n", complexFunction(&myArray, sumArray));
    
    return 0;
}