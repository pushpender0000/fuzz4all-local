#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    for (size_t i = 0; i < ARRAY_SIZE / 2; ++i) {
        func((int32_t)i * (ARRAY_SIZE / 2 - i), ((uint8_t[4]){(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}));
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
        arrayOfStructs[i] = (MyStruct){(int32_t)(10 * i + i), {(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}};
    }
}

void printArray() {
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += arrayOfStructs[i].data;
    }
    printf("%llu\n", totalHash);
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
    printArray();

    // Additional test with complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        complexFunction(i, newBytes);
    }
    printf("After complex function call:\n");
    printArray();

    return 0;
}