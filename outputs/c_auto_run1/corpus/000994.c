#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 30
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i].data = (i % 2 == 0) ? ((int64_t)i * 10LL) : -((int64_t)i * 10LL);
        for (int j = 0; j < 4; ++j) {
            arrayOfStructs[i].bytes[j] = (uint8_t)(i * 3 + j);
        }
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%ld\n", arrayOfStructs[i].data);
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void complexFunction(int64_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset].data = 100LL + ((int64_t)offset * 10LL);
        for (int i = 0; i < 4; ++i) {
            arrayOfStructs[offset].bytes[i] = newBytes[i];
        }
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFunc)(int64_t, uint8_t[4]);

void runTests(TestFunc func) {
    int64_t vals[] = {10LL, -10LL, 300LL, -300LL};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[] = {(uint8_t)(i * 2), (uint8_t)(i * 2 + 1), (uint8_t)(i * 2 + 2), (uint8_t)(i * 2 + 3)};
        func(vals[i], arr);
    }
}

void testFunction(int64_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%u\n", hashStruct(&s));
}

void testFunctionPointer() {
    TestFunc funcPtr = testFunction;
    runTests(funcPtr);
}

int main() {
    initializeArray();
    testFunctionPointer();
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printArray();
    return 0;
}