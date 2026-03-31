#include <stdio.h>
#include <stdint.h>

typedef uint32_t uint;

#define ARRAY_SIZE 1000 // Increase array size significantly

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void initializeArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i; // Increase complexity with arithmetic operations
    }
}

uint calculateSum(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 5 == 0) {
            sum += arr->data[i] * 2; // More complex operations with different modulo conditions
        } else if (i % 5 == 1) {
            sum -= arr->data[i] / 2; // Subtraction and division for more complexity
        } else if (i % 5 == 2) {
            sum *= arr->data[i]; // Multiplication to increase complexity further
        } else if (i % 5 == 3) {
            sum |= arr->data[i] << 1; // Bitwise operations for added complexity
        } else {
            sum &= arr->data[i]; // Bitwise AND operation
        }
    }
    return sum;
}

void printResult(const ArrayStruct *arr) {
    printf("%u\n", calculateSum(arr));
}

typedef uint (*FuncPtr)(const ArrayStruct*);

uint complexFunction(const ArrayStruct *arr) {
    FuncPtr func = calculateSum;
    return func(arr) + 5; // Function pointer usage and additional arithmetic operation for complexity
}

int main() {
    ArrayStruct myArray;
    initializeArray(&myArray, 10);
    printResult(&myArray);
    printf("%u\n", complexFunction(&myArray));
    return 0;
}