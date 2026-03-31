#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50
#define MAX(a, b) ((a > b) ? a : b)

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

MyStruct arrayOfStructs[ARRAY_SIZE];

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1] + 5, arr[2], arr[3]}})

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    return (uint32_t)(s->data + 100) ^ ((uint32_t)s->bytes[0] << 8 | (uint32_t)s->bytes[1] >> 4);
}

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
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

void runFunctionPointerTest() {
    TestFunc funcPtr = testFunction;
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        funcPtr(vals[i], arr[i]);
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
        printStruct(&arrayOfStructs[i]);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    runFunctionPointerTest();

    return 0;
}