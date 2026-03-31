#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 100
#define INITIAL_VALUE(x) ((x)->a + (x)->b * 2 - (x)->c / 3 + (x)->d % 4)

typedef struct {
    int32_t a;
    uint8_t b, c, d;
} ComplexStruct;

typedef void (*FuncPtr)(ComplexStruct*);

// Macro to create a complex struct with specific values
#define CREATE_COMPLEX(a, b, c, d) ((ComplexStruct){(a), (b), (c), (d)})

// Inline function to initialize a struct and handle out-of-bounds checks
static inline void initStructInline(ComplexStruct array[], int index, uint8_t newBytes[4]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        array[index] = CREATE_COMPLEX(10 * index + index % 5, newBytes[0], newBytes[1], newBytes[2]);
    } else {
        printf("Index out of bounds\n");
    }
}

// Function to create a complex struct with specific values
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s = {val, arr[0], arr[1], arr[2]};
    return s;
}

// Function to print the data part of a struct
void printStruct(const ComplexStruct *s) {
    printf("%d\n", s->a);
}

ComplexStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array with complex struct values and avoid specific indices
void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += INITIAL_VALUE(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to test the function pointer usage with complex struct manipulation
void testFunctionWithPointer(ComplexStruct array[], int index, uint8_t newBytes[4]) {
    initStructInline(array, index, newBytes);
    printStruct(&array[index]);
}

FuncPtr funcPtr = testFunctionWithPointer;

// Function to run tests with a function pointer using the typedef and complex struct manipulation
void runTestsWithPointer() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        funcPtr(arrayOfStructs, i, arr[i]);
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer();
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    return 0;
}