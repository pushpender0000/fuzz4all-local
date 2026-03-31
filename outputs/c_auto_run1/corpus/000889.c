#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 20

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void createComplexStruct(MyStruct *s, int32_t val, const uint8_t arr[]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

uint32_t hashComplexStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 3; // Different divisor for complexity
        }
    }
    return h;
}

#define INITIAL_VALUE 10
#define UPDATE_VALUE(x, y) ((x + y) * 2 - (x - y))

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s;
    createComplexStruct(&s, x, y);
    printf("%u\n", hashComplexStruct(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        int32_t val = INITIAL_VALUE * i;
        if (i == 5) {
            continue; // Skip initialization to test undefined behavior
        }
        createComplexStruct(&arrayOfStructs[i], val, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) {
            break; // Test early exit and undefined behavior
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue; // Skip some to test optimizer behavior
        }
        totalHash += hashComplexStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        createComplexStruct(&arrayOfStructs[offset], UPDATE_VALUE(10 * offset, 5), newBytes);
    } else {
        printf("Offset out of bounds\n"); // Test error handling
    }
}

void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}