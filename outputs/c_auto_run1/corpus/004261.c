#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i].data = i * 2;
        arrayOfStructs[i].bytes[0] = (uint8_t)(i + 1);
        arrayOfStructs[i].bytes[1] = (uint8_t)(i + 2);
        arrayOfStructs[i].bytes[2] = (uint8_t)(i + 3);
        arrayOfStructs[i].bytes[3] = (uint8_t)(i + 4);
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset].data = offset * 5;
        arrayOfStructs[offset].bytes[0] = newBytes[0];
        arrayOfStructs[offset].bytes[1] = newBytes[1];
        arrayOfStructs[offset].bytes[2] = newBytes[2];
        arrayOfStructs[offset].bytes[3] = newBytes[3];
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1] + 5, y[2], y[3]}};
    printf("%d\n", s.data);
}

void runTests() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunction(vals[i], arr[i]);
    }
}

void runTestsWithPointer() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunction(vals[i], arr[i]);
    }
}

int main() {
    initializeArray();
    runTestsWithPointer();
    printf("After second set of tests:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += arrayOfStructs[i].data;
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}