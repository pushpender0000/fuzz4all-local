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
        if ((i & 7) == 0 || (i & 15) == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){.data = i * 10, .bytes = {i % 256, (uint8_t)(i + 1), (uint8_t)(i + 2), (uint8_t)(i + 3)}};
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[4] = {(uint8_t)(vals[i] % 256), (uint8_t)(vals[i] + 1), (uint8_t)(vals[i] + 2), (uint8_t)(vals[i] + 3)};
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if ((h & 1) == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void printHash(const MyStruct *s) {
    printf("%u\n", hashStruct(s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i & 3) == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printStruct(&arrayOfStructs[i]);
        printHash(&arrayOfStructs[i]);
    }
    return 0;
}