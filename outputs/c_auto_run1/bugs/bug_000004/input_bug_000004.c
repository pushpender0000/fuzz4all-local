#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 13 == 0)) continue; // Avoid specific indices to avoid undefined behavior
        arrayOfStructs[i] = (MyStruct){i * 10, {(uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3), (uint8_t)(i + 4)}};
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[] = {(uint8_t)(i + 5), (uint8_t)(i + 6), (uint8_t)(i + 7), (uint8_t)(i + 8)};
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
    uint32_t h = (uint32_t)s.data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s.bytes[i] * 2;
        } else {
            h += s.bytes[i] / 2;
        }
    }
    printf("%u\n", h);
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        MyStruct *s = &arrayOfStructs[i];
        totalHash += s->data + ((uint32_t)s->bytes[0] * 2 + (uint32_t)s->bytes[1] / 2);
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
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
    uint32_t h = (uint32_t)s.data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s.bytes[i] * 2;
        } else {
            h += s.bytes[i] / 2;
        }
    }
    printf("%u\n", h);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[] = {(uint8_t)(i + 5), (uint8_t)(i + 6), (uint8_t)(i + 7), (uint8_t)(i + 8)};
        func(vals[i], arr);
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
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}