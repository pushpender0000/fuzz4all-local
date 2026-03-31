#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%u\n", (uint32_t)s.data + (uint32_t)s.bytes[0] * 2 + (uint32_t)s.bytes[1] / 2 + (uint32_t)s.bytes[2] * 3 - (uint32_t)s.bytes[3] / 3);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){10 * i, initialArray};
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += ((uint32_t)arrayOfStructs[i].data + (uint32_t)arrayOfStructs[i].bytes[0] * 2 + (uint32_t)arrayOfStructs[i].bytes[1] / 2 + (uint32_t)arrayOfStructs[i].bytes[2] * 3 - (uint32_t)arrayOfStructs[i].bytes[3] / 3);
    }
    printf("Total Hash: %u\n", totalHash);

    // Additional complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%u\n", ((uint32_t)arrayOfStructs[i].data + (uint32_t)arrayOfStructs[i].bytes[0] * 2 + (uint32_t)arrayOfStructs[i].bytes[1] / 2 + (uint32_t)arrayOfStructs[i].bytes[2] * 3 - (uint32_t)arrayOfStructs[i].bytes[3] / 3));
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += ((uint32_t)arrayOfStructs[i].data + (uint32_t)arrayOfStructs[i].bytes[0] * 2 + (uint32_t)arrayOfStructs[i].bytes[1] / 2 + (uint32_t)arrayOfStructs[i].bytes[2] * 3 - (uint32_t)arrayOfStructs[i].bytes[3] / 3);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}