#include <stdio.h>
#include <stdint.h>

// Define a complex type for demonstration
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to calculate the size of an array at compile time
#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the struct array
void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = (MyStruct){.data = i * 10, .bytes = {i, i + 1, i + 2, i + 3}};
    }
}

// Function to hash a struct
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i] * (i + 1);
    }
    return h;
}

// Function to print struct data
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Define a function pointer type for testing
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Macro to iterate over an array and apply a function
#define RUN_TESTS(func) { \
    int32_t vals[] = {10, -10, 300, -300}; \
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) { \
        func(vals[i], (uint8_t[4]){i * 2, i * 2 + 1, i * 2 + 2, i * 2 + 3}); \
    } \
}

// Function to test the function pointer usage
void runTestsWithFunctionPointer() {
    TestFunc funcPtr = &testFunction;
    RUN_TESTS(funcPtr);
}

// The main test function
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Function to demonstrate complex function usage
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

int main() {
    initializeArray();
    runTestsWithFunctionPointer();
    
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0) continue; // Skip every 7th element to increase complexity
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes); // Modify the middle element of the array
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break; // Stop after the 7th element to create a controlled interruption in iteration
        printStruct(&arrayOfStructs[i]);
    }
    
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0) continue; // Skip every 7th element again to maintain the pattern of skipping in different contexts
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}