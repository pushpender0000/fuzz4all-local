#include <stdio.h>
#include <stdint.h>

// Define constants
#define ARRAY_SIZE 50
#define INITIAL_VALUE 100
#define OFFSET_BASE 20
#define NEW_BYTES {9, 10, 11, 12}

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Define the struct type
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to initialize the array of structs with complex conditions
void initializeArray(MyStruct *array) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = CREATESTRUCT(INITIAL_VALUE + i * OFFSET_BASE, initialArray);
    }
}

// Function prototype for function pointer test
void runTestsWithPointer(void (*func)(int32_t, uint8_t[4]));

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to perform a complex operation with an offset and new bytes
void complexFunction(MyStruct *array, int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = CREATESTRUCT(INITIAL_VALUE + offset * OFFSET_BASE, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to run tests with a function pointer
void runTestsWithPointer(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], NEW_BYTES);
    }
}

// Function to test the function pointer usage
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

int main() {
    initializeArray(arrayOfStructs);
    runTestsWithPointer(testFunctionWithPointer);
    printf("After function pointer tests:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }

    // Additional complex function call with an out-of-bounds offset
    uint8_t newBytes[] = NEW_BYTES;
    complexFunction(arrayOfStructs, ARRAY_SIZE + 10, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }

    return 0;
}