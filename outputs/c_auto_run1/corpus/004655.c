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
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){{1, 2, 3, 4}}); // Fixed array for consistency
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){10 * i, {42}}; // Fixed value for bytes
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += arrayOfStructs[i].data;
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){{1, 2, 3, 4}}); // Fixed array for consistency
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    complexFunction(ARRAY_SIZE / 2, (uint8_t[4]){{9, 10, 11, 12}});
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}