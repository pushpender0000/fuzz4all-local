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
        if (i % 3 == 0) { // Increased complexity by using a different condition
            sum += arr->data[i] * 3; // Complex operation with multiplication
        } else if (i % 4 == 0) { // Another complex condition for increased variability
            sum += arr->data[i] / 3; // Division added to increase complexity
        } else {
            sum += arr->data[i]; // Basic addition for clarity and variety
        }
    }
    return sum;
}

#define PRINT_SUM(arr) printf("%u\n", sumArray(arr))

typedef uint (*FuncPtr)(const ArrayStruct*);

uint doubleSum(const ArrayStruct *arr) {
    FuncPtr func = sumArray; // Function pointer usage for complexity and flexibility
    return func(arr) * 2 + 100; // Multiplication by 2 plus an additional constant for stress
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    PRINT_SUM(&myArray);
    printf("%u\n", doubleSum(&myArray));
    return 0;
}