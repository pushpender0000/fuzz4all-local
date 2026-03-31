#include <stdio.h>
#include <stdint.h>

// Define a union with a flexible array member (FAM) for fuzzing memory handling
typedef union {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Define an array of unions
#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

// Macro to initialize the array with specific values using a function pointer
void initializeArray(MyStruct* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = (MyStruct){.data = (int32_t)(i * 10), .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
    }
}

// Function to print the data part of a MyStruct using function pointers
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the struct using specific rules and return it as an array for further processing
uint8_t* hashStruct(const MyStruct *s, uint8_t result[4]) {
    int32_t h = (int32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    result[0] = (uint8_t)(h & 0xFF);
    result[1] = (uint8_t)((h >> 8) & 0xFF);
    result[2] = (uint8_t)((h >> 16) & 0xFF);
    result[3] = (uint8_t)((h >> 24) & 0xFF);
    return result;
}

// Function to run tests with function pointers and complex parameter handling
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Test function to demonstrate usage of structs and functions with complex parameter handling
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    uint8_t hashResult[4];
    hashStruct(&s, hashResult);
    for (int i = 0; i < 4; ++i) {
        printf("%d ", hashResult[i]);
    }
    printf("\n");
}

// Macro to define a function pointer and invoke it with specific arguments
#define RUN_TESTS() runTests(testFunction)

int main() {
    initializeArray(arrayOfStructs, ARRAY_SIZE); // Initialize the array of structs
    RUN_TESTS();        // Use function pointers to test different functionalities
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        uint8_t hashResult[4];
        totalHash += *(uint32_t*)hashStruct(&arrayOfStructs[i], hashResult);
    }
    printf("Total Hash: %u\n", totalHash); // Print the accumulated hash value

    return 0;
}