#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024
#define HASH_MULTIPLIER 5
#define INITIAL_VALUE 800

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint64_t calculateComplexHash(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(INITIAL_VALUE + offset * HASH_MULTIPLIER, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }

    uint64_t hash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 9 == 0 || i % 17 == 0) { // More complex conditions to avoid specific indices
            continue;
        }
        hash += ((uint64_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 3 + array[i].bytes[2] * 4 - array[i].bytes[3]);
    }
    return hash;
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", ((uint64_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 3 + s.bytes[2] * 4 - s.bytes[3]));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {100, -150, 350, -400};
    uint8_t arr[][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}, {90, 100, 110, 120}, {130, 140, 150, 160}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {90, 100, 110, 120};
    MyStruct arrayOfStructs[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 8 == 0 || i % 16 == 0) { // Even more complex conditions to avoid specific indices
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