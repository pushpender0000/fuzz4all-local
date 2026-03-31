#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 1024
MyStruct arrayOfStructs[ARRAY_SIZE];

#define INITIALIZE_STRUCT(index, value) \
    arrayOfStructs[index] = (MyStruct){value, {((uint8_t)(value)), ((uint8_t)(value >> 8)), ((uint8_t)(value >> 16)), ((uint8_t)(value >> 24))}}

void initializeComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        INITIALIZE_STRUCT(i, (int32_t)(i * 10));
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += arrayOfStructs[i].data + arrayOfStructs[i].bytes[0] * 2 + arrayOfStructs[i].bytes[1] / 2 + arrayOfStructs[i].bytes[2] * 3 - arrayOfStructs[i].bytes[3];
    }
    return totalHash;
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){(int32_t)(100 + 10 * i), newBytes};
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    stressTest();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after stressTest: %u\n", totalHash);

    return 0;
}