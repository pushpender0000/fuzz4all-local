#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro to calculate hash based on struct contents
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

// Define a struct
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototypes
void testFunction(int32_t x, uint8_t y[4]);
uint32_t calculateTotalHash();
void complexFunction(int32_t offset, uint8_t newBytes[4]);
void runTests(void (*func)(int32_t, uint8_t[4]));

// Global array of structs
MyStruct arrayOfStructs[50];

// Initialize the array with specific values and indices to avoid simple patterns
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print data from the struct array
void printArray() {
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

// Function to test function pointer usage
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to calculate the total hash of the array using a function pointer
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < 50; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to manipulate the struct array using a complex function
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 50) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Main function to demonstrate the usage of all defined functions and complex manipulations
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(49, newBytes); // Use an out-of-bounds offset to ensure robustness
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}