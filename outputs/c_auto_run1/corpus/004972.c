#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 512
#define HASH_MULTIPLIER 37
#define INITIAL_VALUE 999

typedef struct {
    int64_t data;
    uint8_t bytes[8];
} MyStruct;

MyStruct createComplexStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

uint64_t calculateComplexHash(MyStruct array[], int32_t offset, uint8_t newBytes[8]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(INITIAL_VALUE + offset * HASH_MULTIPLIER, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }

    uint64_t hash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 5 == 0 || i % 7 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        hash += ((uint64_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return hash;
}

void testFunctionWithPointer(int64_t x, uint8_t y[8]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", ((uint64_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

typedef void (*TestFuncPtr)(int64_t, uint8_t[8]);

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {100, -100, 3000, -3000};
    uint8_t arr[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24}, {25, 26, 27, 28, 29, 30, 31, 32}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {17, 18, 19, 20, 21, 22, 23, 24};
    MyStruct arrayOfStructs[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 5 == 0 || i % 7 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(INITIAL_VALUE + i * HASH_MULTIPLIER, newBytes);
    }
}

int main() {
    stressTest();
    runTestsWithPointer(testFunctionWithPointer);

    return 0;
}