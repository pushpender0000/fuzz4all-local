#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int64_t, uint8_t*);

void createStruct(MyStruct *s, int64_t val, const uint8_t arr[]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

#define ARRAY_SIZE 30
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5 || i == 7) continue; // Avoiding specific indices to increase complexity
        createStruct(&arrayOfStructs[i], 10LL * i, initialArray);
    }
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Avoiding every third element to add complexity
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int64_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        createStruct(&arrayOfStructs[offset], 100LL + 10LL * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int64_t x, uint8_t y[4]) {
    MyStruct s;
    createStruct(&s, x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void runTests(TestFunc func) {
    int64_t vals[] = {10LL, -10LL, 300LL, -300LL};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunctionPointer() {
    TestFunc funcPtr = testFunction;
    runTests(funcPtr);
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
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (arrayOfStructs[i].data != 0) printStruct(&arrayOfStructs[i]); // Ensure not zero to avoid simplifying
    }
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}