#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 512
#define HASH_MULTIPLIER 3
#define INITIAL_VALUE 500

typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

uint64_t calculateComplexHash(MyStruct array[], int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(INITIAL_VALUE + offset * HASH_MULTIPLIER, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }

    uint64_t hash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        hash += ((uint64_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return hash;
}

void testFunctionWithPointer(int64_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", ((uint64_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

typedef void (*TestFuncPtr)(int64_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {100, -100, 3000, -3000};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    MyStruct arrayOfStructs[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
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