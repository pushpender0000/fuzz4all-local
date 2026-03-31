#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define a complex macro for struct creation
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Define a macro to calculate the hash of a struct (complex version)
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize an array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the struct data
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Define a function pointer for testing
void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to print the structs in the array with complex conditions
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to perform a complex operation with an offset and new bytes
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test the function pointer usage
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

#define ARRAY_SIZE 50

MyStruct arrayOfStructs[ARRAY_SIZE];

int main() {
    initializeArray();
    runTestsWithPointer(testFunctionWithPointer);
    printArray();

    // Additional complex function call to stress the optimizer and parser
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();

    return 0;
}