#include <stdio.h>

#define ARRAY_SIZE 1024
typedef unsigned int uint;

typedef struct {
    uint data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, uint value) {
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

uint sumEvenIndexedElements(const ArrayStruct *arr) {
    uint sum = 0;
    for (uint i = 0; i < ARRAY_SIZE; i += 2) { // Only summing even indexed elements
        sum += arr->data[i];
    }
    return sum;
}

uint multiplyByIndex(const ArrayStruct *arr, uint index) {
    if (index >= ARRAY_SIZE) {
        printf("Error: Index out of bounds\n"); // Handling potential error gracefully
        return 0;
    }
    return arr->data[index] * index;
}

typedef uint (*FuncPtr)(const ArrayStruct*, uint);

uint complexOperation(const ArrayStruct *arr, FuncPtr func) {
    uint result = 0;
    for (uint i = 0; i < ARRAY_SIZE; i++) {
        if (i % 2 == 0) {
            result += func(arr, i); // Using function pointer and complex operation
        } else {
            result -= func(arr, i); // Subtracting results for more complexity
        }
    }
    return result;
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    
    FuncPtr func = multiplyByIndex;
    uint finalResult = complexOperation(&myArray, func);
    
    printf("%u\n", finalResult); // Output the result
    return 0;
}