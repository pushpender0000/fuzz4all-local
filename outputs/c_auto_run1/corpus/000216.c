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

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 3 == 0) { // Complex operation to stress the optimizer further
            sum += arr->data[i] * 3; // More complex operation with multiplication by 3
        } else if (i % 2 == 0) {
            sum -= arr->data[i] / 2; // Subtracting half of the value
        } else {
            sum += arr->data[i] * 1.5; // Multiplying by 1.5 for floating-point stress
        }
    }
    return sum;
}

#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

typedef uint (*FuncPtr)(const ArrayStruct*);

uint complexSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    uint result = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 5 == 0) { // Further increase complexity with modulo operation
            result += func(arr); // Using function pointer and calling the sum function inside loop
        } else {
            result -= arr->data[i] / 2; // Subtracting half of the value within the same complex structure
        }
    }
    return result * 3; // Final multiplication for increased stress on optimizer and runtime calculations
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    PRINT_SUM(&myArray);
    printf("%u\n", complexSum(&myArray));
    return 0;
}