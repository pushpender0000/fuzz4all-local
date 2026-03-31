#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

// Macro to calculate the hash of a struct with additional complexity
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 - (s)->bytes[1] / 2 + (s)->bytes[2] * 3 ^ (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values, including complex initialization
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1] * 2, arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to print the data part of a struct with additional formatting
void printStruct(const MyStruct *s) {
    printf("Data: %d, Bytes: [%u, %u, %u, %u]\n", s->data, s->bytes[0], s->bytes[1], s->bytes[2], s->bytes[3]);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with given values and avoid simple patterns
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions and additional operations
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to perform a complex operation with an offset and new bytes, including additional operations in the function itself
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
        printf("Offset %d updated with data: %d\n", offset, arrayOfStructs[offset].data);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunction);
    printf("After first set of tests:\n");
    printArrayWithPointer();
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}