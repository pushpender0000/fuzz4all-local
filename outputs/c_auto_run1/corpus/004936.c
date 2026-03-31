#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

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
            break;
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

void complexFunction(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests(TestFunc func) {
    for (size_t i = 0; i < ARRAY_SIZE / 2; ++i) {
        func(i * 10 - 50, ((uint8_t[4]){(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}));
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    for (size_t i = 0; i < ARRAY_SIZE / 2; ++i) {
        func(i * 10 - 50, ((uint8_t[4]){(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}));
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunction);
    printf("After second set of tests:\n");
    printArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}