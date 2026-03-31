#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024
#define HASH_FACTOR 37 // A prime number for hashing function

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

static inline uint64_t HASH(MyStruct *s) {
    return (uint64_t)(s->data + s->bytes[0] * 2 + s->bytes[1] / 2 - s->bytes[2] * 3 + s->bytes[3]);
}

typedef void (*TestFunc)(int64_t, uint8_t[8]);

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

void testFunctionWithPointer(int64_t x, uint8_t y[8]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int64_t, uint8_t[8]);

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {10, -10, 300, -300, INT64_MAX, INT64_MIN};
    uint8_t arr[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24}, {25, 26, 27, 28, 29, 30, 31, 32}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexFunction(MyStruct array[], int64_t offset, uint8_t newBytes[8]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12, 13, 14, 15, 16};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        complexFunction(arrayOfStructs, i, newBytes);
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    printf("Total Hash: %lu\n", totalHash);

    return 0;
}