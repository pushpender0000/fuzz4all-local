#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef uint32_t (*HashFunc)(const MyStruct *);

uint32_t simpleHash(const MyStruct *s) {
    return (uint32_t)(s->data + s->bytes[0] * 2 + s->bytes[1] / 2 + s->bytes[2] * 3 - s->bytes[3]);
}

MyStruct createStruct(int32_t val, uint8_t bytes[4]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.bytes[i] = bytes[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += simpleHash(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    else printf("Offset out of bounds\n");
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", simpleHash(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) break; // Avoid specific indices to avoid undefined behavior
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunction);
    printf("After first set of tests:\n");
    printArrayWithPointer();
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}