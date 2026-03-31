#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define a union with nested structs for complex data representation
typedef union {
    struct {
        int8_t a;
        int16_t b;
        uint32_t c : 24; // Bit-field to test specific bit handling
    } parts;
    float combined;
} MixedUnion;

// Function prototypes for complex operations
void complexOperation(const MixedUnion *mu, void (*printFunc)(uint64_t));
void printInteger(uint64_t num);
void runTests(void (*func)(int32_t, uint8_t[4]));
void testFunction(int32_t x, uint8_t y[4]);

// Implementation of the function pointer usage and complex operations
void complexOperation(const MixedUnion *mu, void (*printFunc)(uint64_t)) {
    int64_t result = (int64_t)mu->parts.a + mu->parts.b + (int64_t)mu->parts.c;
    printFunc((uint64_t)result);
}

void printInteger(uint64_t num) {
    printf("%llu\n", num);
}

// Define a function to initialize mixed union array and test the complexOperation
void initializeArrayAndTest() {
    MixedUnion muArray[5];
    for (int i = 0; i < 5; ++i) {
        muArray[i].parts.a = i - 10;
        muArray[i].parts.b = i * 2000;
        muArray[i].parts.c = (uint32_t)(i + 200);
    }

    // Test the function pointer with complexOperation
    void (*testFunc)(const MixedUnion*, void(*)(uint64_t)) = complexOperation;
    testFunc(muArray, printInteger);
}

// Function to run tests with function pointers
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Test function to demonstrate usage of structs and functions
void testFunction(int32_t x, uint8_t y[4]) {
    MixedUnion s = (MixedUnion){.combined = *(float*)&x}; // Bit manipulation for fun!
    printf("%f\n", s.combined); // Print the float representation of int
}

// Macro to define a function pointer and invoke it with specific arguments
#define RUN_TESTS() runTests(testFunction)

int main() {
    initializeArrayAndTest(); // Initialize the array of mixed unions and test the operations
    RUN_TESTS();               // Use function pointers to test different functionalities

    return 0;
}