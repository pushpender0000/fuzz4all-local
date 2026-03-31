#include <stdio.h>
#include <stdint.h>

// Define a macro for array size
#define ARRAY_SIZE 100

// Typedef for clarity
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to initialize the structure
void createStruct(MyStruct *s, int32_t val, const uint8_t arr[]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
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

// Function to print the structure data (deterministic output)
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Array of structures
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structures
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        createStruct(&arrayOfStructs[i], 10 * i, initialArray);
    }
}

// Function to print the array of structures (deterministic output)
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of the array of structures
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to perform complex manipulation using a function pointer
void runTests(void (*func)(int32_t, uint8_t[])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test a specific function using a function pointer
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s;
    createStruct(&s, x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Main function to initialize the array and run tests with a function pointer
int main() {
    initializeArray();
    runTests(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}