#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro to calculate the hash of a struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize an array of structs with complex conditions
void initializeArray(MyStruct* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if ((i + 1) % 7 == 0 || (i + 1) % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arr[i] = CREATESTRUCT(10 * i, (uint8_t[]){i, i+1, i+2, i+3});
    }
}

// Function to print the structs in the array with complex conditions
void printArray(MyStruct* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if ((i + 1) % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printf("%d\n", arr[i].data);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions
uint32_t calculateTotalHash(MyStruct* arr, size_t size) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < size; ++i) {
        if ((i + 1) % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arr[i]);
    }
    return totalHash;
}

// Function to perform a complex operation with an offset and new bytes
void complexFunction(MyStruct* arr, size_t size, int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < size) {
        arr[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test the function pointer usage
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[]){i, i+1, i+2, i+3});
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printf("%d\n", s.data);
    printf("%u\n", HASH(&s));
}

MyStruct arrayOfStructs[50];

int main() {
    initializeArray(arrayOfStructs, 50);
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs, 50);
    printf("Total Hash: %u\n", totalHash);

    // Additional complex function call to stress the optimizer and parser
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, 50, 24, newBytes);
    printf("After complex function call:\n");
    printArray(arrayOfStructs, 50);
    totalHash = calculateTotalHash(arrayOfStructs, 50);
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}