#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro to calculate a complex hash for a struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 - (s)->bytes[1] / 4 + (s)->bytes[2] * 3 + (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize an array of structs with complex conditions
void initializeArray(MyStruct *array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 13 == 0) && i != 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = CREATESTRUCT(10 * (i + 1), (uint8_t[]){(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)});
    }
}

// Function to print the data part of a struct and its hash
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer using an array of structs
void runTests(MyStruct *array, TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], array[i].bytes);
    }
}

// Function to perform a complex operation with an offset and new bytes
void complexFunction(MyStruct *array, int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test the function pointer usage with an array of structs
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

#define ARRAY_SIZE 100

MyStruct arrayOfStructs[ARRAY_SIZE];

int main() {
    initializeArray(arrayOfStructs);
    runTests(arrayOfStructs, testFunctionWithPointer);

    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    // Perform a complex function call with an offset and new bytes
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 13 == 0) && i != 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}