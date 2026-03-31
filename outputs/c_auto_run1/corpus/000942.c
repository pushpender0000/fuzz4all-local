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
        if (i == 50) continue; // Avoid index 50 to avoid undefined behavior
        arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {4, 3, 2, 1}};
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

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){4, 3, 2, 1});
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 75) continue; // Avoid index 75 to avoid undefined behavior
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 75) break; // Avoid index 75 to avoid undefined behavior
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 75) continue; // Avoid index 75 to avoid undefined behavior
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}