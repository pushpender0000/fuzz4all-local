#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro to calculate the hash of a struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct *array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = CREATESTRUCT(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

TestFunc funcPtr;

void runTests() {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        funcPtr(vals[i], (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

void runTestsWithPointer() {
    TestFunc func = testFunction;
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

int main() {
    MyStruct arrayOfStructs[5];
    initializeArray(arrayOfStructs, 5);
    funcPtr = testFunction;
    runTests();
    return 0;
}