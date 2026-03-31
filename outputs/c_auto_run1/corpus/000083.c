#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 100

typedef unsigned int uint;

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

// Macro to fill the array with a specific pattern
#define FILL_ARRAY(arr, start) do { \
        for (uint i = 0; i < ARRAY_SIZE; ++i) { \
            arr.data[i] = (start + i); \
        } \
    } while (0)

// Macro to calculate the sum of array elements with a specific operation
#define SUM_ARRAY(arr, op) do { \
        uint sum = 0; \
        for (uint i = 0; i < ARRAY_SIZE; ++i) { \
            if (op == '+') { \
                sum += arr.data[i]; \
            } else if (op == '*') { \
                sum *= arr.data[i]; \
            } \
        } \
        printf("%u\n", sum); \
    } while (0)

// Inline function to fill the array with a specific pattern
static inline void fillArray(ArrayStruct *arr, uint start) {
    for (uint i = 0; i < ARRAY_SIZE; ++i) {
        arr->data[i] = (start + i);
    }
}

// Inline function to calculate the sum of array elements with a specific operation
static inline void sumArray(const ArrayStruct *arr, char op) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; ++i) {
        if (op == '+') {
            sum += arr->data[i];
        } else if (op == '*') {
            sum *= arr->data[i];
        }
    }
    printf("%u\n", sum);
}

typedef uint (*FuncPtr)(const ArrayStruct*);

// Function to calculate the double of the array sum using a function pointer
uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = (FuncPtr)&sumArray;
    return func(arr) * 2;
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10); // Fill the array with values starting from 10
    sumArray(&myArray, '+'); // Calculate the sum of the array elements using addition
    printf("%u\n", doubleSum(&myArray)); // Print the result of doubleSum function
    return 0;
}