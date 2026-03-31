#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define HASH(s) ((uint32_t)(s.data + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]))

typedef void (*TestFunc)(int32_t, uint8_t[4]);

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

static inline uint32_t HASH(MyStruct *s) {
    return (uint32_t)(s->data + s->bytes[0] * 2 + s->bytes[1] / 2 + s->bytes[2] * 3 - s->bytes[3]);
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexFunction(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        complexFunction(arrayOfStructs, i, newBytes);
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += HASH(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    return 0;
}