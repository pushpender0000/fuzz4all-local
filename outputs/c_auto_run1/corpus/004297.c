#include <stdio.h>
#include <stdint.h>

// Macro to calculate a hash value for a structure
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

// Define the structure
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a structure instance
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function prototypes
void initializeArray();
void printStruct(const MyStruct *s);
uint32_t calculateTotalHash();
void complexFunction(int32_t offset, uint8_t newBytes[4]);
void testFunctionWithPointer(int32_t x, uint8_t y[4]);
void runTestsWithPointer(TestFuncPtr func);
void printArrayWithPointer();

// Global array of structures
MyStruct arrayOfStructs[50];

// Function to initialize the array with complex conditions
void initializeArray() {
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, (uint8_t[]){(uint8_t)(i), (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)});
    }
}

// Function to print the data part of a structure
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to calculate the total hash of all structures in the array
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

// Function to perform a complex operation with an offset and new bytes
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 50) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test the function pointer usage
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer
void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){(uint8_t)(i*2), (uint8_t)(i*2+1), (uint8_t)(i*2+2), (uint8_t)(i*2+3)});
    }
}

// Function to print the structs in the array with complex conditions
void printArrayWithPointer() {
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    printArrayWithPointer();
    uint32_t totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}