#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

void initializeArray(MyStruct array[]) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = (MyStruct){10 * i, {(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}};
    }
}

void printArray(MyStruct array[]) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        printf("%d\n", array[i].data);
    }
}

uint32_t calculateTotalHash(MyStruct array[]) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += array[i].data;
    }
    return totalHash;
}

void complexFunction(MyStruct array[], int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTests(TestFuncPtr func) {
    for (size_t i = 0; i < ARRAY_SIZE / 2; ++i) {
        func((int32_t)((i * 10 - 50) + (i % 2 ? 1 : 0)), ((uint8_t[4]){(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}));
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);

    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash after complex function: %u\n", totalHash);

    return 0;
}