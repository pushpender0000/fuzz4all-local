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

uint complexOperation(const ArrayStruct *arr, uint index) {
    if (index % 3 == 0) {
        return arr->data[index] << 2; // Shift left by 2 for complexity
    } else if (index % 3 == 1) {
        return arr->data[index] >> 1; // Shift right by 1 for more complexity
    } else {
        return arr->data[index] ^ (index * 2); // XOR with index multiplied by 2
    }
}

uint sumArray(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 7 == 0) {
            sum += complexOperation(arr, i); // Use the complex operation in a loop for stress
        } else {
            sum += arr->data[i];
        }
    }
    return sum;
}

#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray;
    return func(arr) * 3; // Use function pointer and multiply result by 3 for increased complexity
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    PRINT_SUM(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}