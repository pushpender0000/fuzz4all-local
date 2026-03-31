#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        func(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){10 * i, {i, i + 1, i + 2, i + 3}};
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += arrayOfStructs[i].data * 2 + arrayOfStructs[i].bytes[0];
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        func(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}