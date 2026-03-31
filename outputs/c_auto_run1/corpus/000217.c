#include <stdio.h>

typedef unsigned int uint;

#define ARRAY_SIZE 100

// Define a structure to hold an array of integers
typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

// Function to fill the array with values based on a starting value
void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i; // Simple linear increase in value
    }
}

// Function to sum the elements of the array with specific operations based on index
uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 3 == 0) { // Complex operation: multiply by 3 when index is divisible by 3
            sum += arr->data[i] * 3;
        } else if (i % 5 == 0) { // Multiply by 5 for indices divisible by 5
            sum += arr->data[i] * 5;
        } else {
            sum += arr->data[i]; // Default operation is addition without special handling
        }
    }
    return sum;
}

#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

// Use a function pointer to call different functions dynamically (in this case, it points to sumArray)
typedef uint (*FuncPtr)(const ArrayStruct*);

uint complexOperation(const ArrayStruct *arr) {
    FuncPtr func = sumArray; // Function pointer pointing to sumArray
    return func(arr) * 2 + 5; // Using function pointer and performing additional operations for complexity
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10); // Fill the array with values starting from 10
    PRINT_SUM(&myArray); // Print the sum of the array elements
    printf("%u\n", complexOperation(&myArray)); // Perform a more complex operation and print the result
    return 0;
}