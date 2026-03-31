#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

#define HASH_CONSTANT 17

#define INITIALIZE_STRUCT(i, val) ((MyStruct){val, {(uint8_t)(i), (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}})

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (!(i % 7 == 0 || i % 13 == 0)) { // Avoid specific indices to avoid undefined behavior
            arrayOfStructs[i] = INITIALIZE_STRUCT(i, 10 * i);
        }
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * HASH_CONSTANT;
        } else {
            h += s->bytes[i] / HASH_CONSTANT;
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
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], ((uint8_t[4]){(uint8_t)(i), (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}));
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    return 0;
}