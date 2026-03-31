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

// Macro to fill the array
#define FILL_ARRAY(arr, value) do { \
    for (uint i = 0; i < ARRAY_SIZE; i++) { \
        (arr).data[i] = (value) + i * (arr).multiplier; \
    } \
} while (0)

// Function to calculate the sum of array elements
uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

// Function using a function pointer to call the sumArray function
uint sumWithPointer(const ArrayStruct *arr) {
    uint (*func)(const ArrayStruct*) = sumArray;
    return func(arr);
}

int main() {
    MultipliedArray myArray;
    myArray.multiplier = 3;
    FILL_ARRAY(myArray.arr, 20); // Using macro for array filling
    printf("%u\n", sumWithPointer(&myArray.arr));
    return 0;
}