#include <stdio.h>
#include <stdint.h>

// Define a struct type for demonstration
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to calculate the size of an array dynamically based on parameters
#define ARRAY_SIZE(a, b) (sizeof(a)/sizeof(a[0]) + b)

// Function prototypes
void initializeArray();
void printStruct(const MyStruct *s);
uint32_t hashStruct(const MyStruct *s);
void runTests(void (*func)(int32_t, uint8_t[4]));
void testFunction(int32_t x, uint8_t y[4]);
void complexFunction(int32_t offset, uint8_t newBytes[4]);
void testFunctionPointerUsage();

// Global array of structs
MyStruct arrayOfStructs[20];

// Initialize the array with specific values
void initializeArray() {
    for (int i = 0; i < 20; ++i) {
        arrayOfStructs[i] = (MyStruct){.data = (i * 10), .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
    }
}

// Function to print the data of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the contents of a struct
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

// Function to run tests using a function pointer
void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage
void testFunctionPointerUsage() {
    void (*funcPtr)(int32_t, uint8_t[4]) = &testFunction;
    runTests(funcPtr);
}

// Main testing function
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Function to set a specific struct in the array with new values
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 20) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

// Main function to demonstrate the functionality
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(10, newBytes); // Testing with an offset that is out of bounds to check error handling

    printf("After complex function call:\n");
    for (int i = 0; i < 20; ++i) {
        if (i == 7) break;
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}