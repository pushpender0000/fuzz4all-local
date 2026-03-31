#include <stdio.h>
#include <stdint.h>

// Define a union with scoped enum
typedef union {
    int32_t data;
    uint8_t bytes[4];
} MyUnion;

// Define an array of unions
MyUnion arrayOfUnions[20];

#define ARRAY_SIZE 20

// Function to initialize the array with specific values
void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 2 == 0) {
            arrayOfUnions[i] = (MyUnion){.data = (i * 10), .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
        } else {
            arrayOfUnions[i] = (MyUnion){.data = -(i * 10), .bytes = {(uint8_t)(i+4), (uint8_t)(i+5), (uint8_t)(i+6), (uint8_t)(i+7)}};
        }
    }
}

// Function to print the data part of a MyUnion
void printUnion(const MyUnion *u) {
    printf("%d\n", u->data);
}

// Function to hash the union using specific rules
uint32_t hashUnion(const MyUnion *u) {
    uint32_t h = (uint32_t)u->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += u->bytes[i] * 3;
        } else {
            h += u->bytes[i] / 3;
        }
    }
    return h;
}

// Function to run tests with function pointers
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Test function to demonstrate usage of unions and functions
void testFunction(int32_t x, uint8_t y[4]) {
    MyUnion u = (MyUnion){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printUnion(&u);
    printf("%u\n", hashUnion(&u));
}

// Macro to define a function pointer and invoke it with specific arguments
#define RUN_TESTS() runTests(testFunction)

int main() {
    initializeArray(); // Initialize the array of unions
    RUN_TESTS();        // Use function pointers to test different functionalities
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashUnion(&arrayOfUnions[i]);
    }
    printf("Total Hash: %u\n", totalHash); // Print the accumulated hash value

    return 0;
}