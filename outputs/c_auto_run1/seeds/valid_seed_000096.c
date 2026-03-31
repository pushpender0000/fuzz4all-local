#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[20];

#define ARRAY_SIZE 20

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = (MyStruct){.data = i * 10, .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){i * 2, i * 3, i * 4, i * 5});
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset].data = 100 + 10 * offset;
        for (int i = 0; i < 4; ++i) {
            arrayOfStructs[offset].bytes[i] = (uint8_t)(offset + i);
        }
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
        if (i % 3 == 0) continue; // Complex loop condition added
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    complexFunction(ARRAY_SIZE / 2);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break; // Complex loop condition added
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Complex loop condition added
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}