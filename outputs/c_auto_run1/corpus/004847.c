#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 512

typedef void (*TestFunc)(uint32_t, uint64_t);

typedef struct {
    uint32_t u32;
    uint64_t u64;
} MyStruct;

MyStruct createComplexStruct(uint32_t val1, uint64_t val2) {
    MyStruct s = {val1, val2};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%u\n", s->u32);
}

#define HASH_CALCULATION(s) ((uint32_t)(s)->u32 + (s)->u64 % 512)

static inline uint32_t hashStruct(const MyStruct *s) {
    return HASH_CALCULATION(s);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, (uint64_t)(1000 + i));
    }
}

void testFunctionWithPointer(uint32_t x, uint64_t y) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFuncPtr)(uint32_t, uint64_t);

void runTestsWithPointer(TestFuncPtr func) {
    uint32_t vals[] = {10, 20, 30, 40};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint64_t)(vals[i] * 10));
    }
}

void stressTest() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(100 + 10 * i, (uint64_t)(2000 + i));
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);

    // Additional test with a function pointer and complex manipulation
    stressTest();

    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash after stressTest: %u\n", totalHash);

    return 0;
}