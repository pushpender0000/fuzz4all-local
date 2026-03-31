#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro for complex computation
#define COMPLEX_COMPUTE(x) ((uint32_t)(x)->data + (x)->bytes[0] * 2 - (x)->bytes[1] / 2 + (x)->bytes[2] * 3 - (x)->bytes[3])

// Typedef for a complex structure
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} ComplexStruct;

// Function to create a complex structure with specific rules
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to print a complex structure
void printStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
}

// Inline function for more efficient but complex operations on the struct array
static inline void manipulateArray(ComplexStruct array[], int32_t index, uint8_t newBytes[4]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        array[index] = createComplexStruct(100 + 10 * index, newBytes);
    } else {
        printf("Index out of bounds\n");
    }
}

// Define a function pointer type
typedef void (*TestFunc)(int32_t, uint8_t[4]);

#define ARRAY_SIZE 50
ComplexStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += COMPLEX_COMPUTE(&arrayOfStructs[i]);
    }
    return totalHash;
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    ComplexStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", COMPLEX_COMPUTE(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
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
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    manipulateArray(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After manipulate array call:\n");
    printComplexArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}