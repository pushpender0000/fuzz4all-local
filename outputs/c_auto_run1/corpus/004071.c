#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro definitions for complex operations
#define ARRAY_SIZE 50
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

// Typedef struct for complex data handling
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototypes
void printStruct(const MyStruct *s);
void runTests(void (*func)(int32_t, uint8_t[4]));
void testFunction(int32_t x, uint8_t y[4]);
void initializeArray();
uint32_t calculateTotalHash();
void complexFunction(int32_t offset, uint8_t newBytes[4]);

// Global array of structs
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with a function pointer
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to initialize the array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
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
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

// Main function to demonstrate the program
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}