#include <stdio.h>

// Define a macro for array size
#define ARRAY_SIZE 1024

// Typedef for unsigned int
typedef unsigned int uint;

// Define a complex struct with nested structures for deeper testing
typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

typedef struct {
    ArrayStruct arr;
    uint multiplier;
} MultipliedArray;

// Macro to fill array with incrementing values
#define FILL_ARRAY(arr, value) for (uint i = 0; i < ARRAY_SIZE; i++) { arr.data[i] = value + i * (arr.multiplier); }

// Function to calculate the sum of an ArrayStruct
uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

// Function using a function pointer to call sumArray
uint useFunctionPointer(const ArrayStruct *arr) {
    uint (*func)(const ArrayStruct*) = sumArray;
    return func(arr);
}

int main() {
    // Initialize the struct and fill it with values
    MultipliedArray myArray;
    myArray.multiplier = 3;
    FILL_ARRAY(myArray, 10);

    // Calculate and print the sum using both direct call and function pointer
    printf("%u\n", sumArray(&myArray.arr));
    printf("%u\n", useFunctionPointer(&myArray.arr));

    return 0;
}