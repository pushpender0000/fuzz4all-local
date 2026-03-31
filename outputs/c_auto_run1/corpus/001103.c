#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[100]; // Increased size to test larger arrays more effectively

void initializeArray() {
    for (int i = 0; i < 100; ++i) {
        if (i != 5) {
            arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {1, 2, 3, 4}};
        }
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i] * (i + 1); // Complex hash function with variable weights
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

#define ARRAY_SIZE 100

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[4] = {i * 2, i * 3, i * 4, i * 5}; // Different byte arrays each time
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset].data = 100 + 10 * offset; // Complex data manipulation
        for (int i = 0; i < 4; ++i) {
            arrayOfStructs[offset].bytes[i] = (uint8_t)(3 * offset + i);
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
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    complexFunction(50); // Stress test with different offsets
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break;
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}