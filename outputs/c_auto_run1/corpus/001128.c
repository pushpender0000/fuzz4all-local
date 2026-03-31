#include <stdio.h>
#include <stdint.h>

// Define a macro for a simple mathematical operation
#define SQUARE(x) ((x) * (x))

// Typedef for clarity in struct definitions
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Global array of structures
MyStruct arrayOfStructs[20];

// Function to initialize the array with complex conditions
void initializeArray() {
    for (int i = 0; i < 20; ++i) {
        if ((i % 3 == 0 && i != 5) || i == 19) { // Complex initialization pattern
            arrayOfStructs[i] = (MyStruct){.data = SQUARE(i), .bytes = {[0] = (uint8_t)i, [1] = (uint8_t)(i+1), [2] = (uint8_t)(i+2), [3] = (uint8_t)(i+3)}};
        } else {
            arrayOfStructs[i] = (MyStruct){.data = -i, .bytes = {[0] = (uint8_t)(i*2), [1] = (uint8_t)(i*2+1), [2] = (uint8_t)(i*2+2), [3] = (uint8_t)(i*2+3)}};
        }
    }
}

// Function to print a structure's data field
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the struct, using bitwise operations and shifts for complexity
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)(s->data >> 8) | ((uint32_t)s->bytes[0] << 16);
    return h;
}

// Typedef for function pointer to match the function signature
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t [4]){(uint8_t)vals[i], (uint8_t)(vals[i]*2), (uint8_t)(vals[i]/3), (uint8_t)(vals[i]-10)});
    }
}

// Implementation of the function for testing with a function pointer
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
}

// Main function to initialize and run the tests
int main() {
    initializeArray();
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);

    // Calculate and print a total hash of all structures for stress testing
    uint32_t totalHash = 0;
    for (int i = 0; i < 20; ++i) {
        if ((i % 5 != 0 && i % 7 != 0) || i == 19) { // Complex condition to exclude some structures from hashing
            totalHash += hashStruct(&arrayOfStructs[i]);
        }
    }
    printf("Total Hash: %u\n", totalHash);

    return 0;
}