#include <stdio.h>
#include <stdint.h>

// Macro definitions for easier readability and maintenance
#define ARRAY_SIZE 30

// Typedefs to make structure declarations more concise
typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int64_t, uint8_t[4]);

// Function prototypes for clarity and to allow main function before definitions
void initializeArray();
void printArray();
uint32_t calculateTotalHash();
void complexFunction(int64_t offset, uint8_t newBytes[4]);
void testFunctionPointer();

// Global array of structures
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to create a structure instance
MyStruct createStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to hash the structure
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

// Function to print the structure data
void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

// Function to initialize the array of structures
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5) {
            continue; // Skip initialization at index 5
        }
        arrayOfStructs[i] = createStruct(10LL * i, initialArray);
    }
}

// Function to print the contents of the array
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) {
            break; // Stop at index 7
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of the array
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue; // Skip every third element
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to manipulate a specific structure in the array
void complexFunction(int64_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100LL + 10LL * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to demonstrate function pointer usage
void testFunctionPointer() {
    TestFunc funcPtr = testFunction;
    int64_t vals[] = {10LL, -10LL, 300LL, -300LL};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        funcPtr(vals[i], arr[i]);
    }
}

// Main function to demonstrate the functionality
int main() {
    initializeArray();
    testFunctionPointer(); // Calling function pointer usage
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional complex manipulation with function pointers and structures
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes); // Adjusted to avoid out of bounds error
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}