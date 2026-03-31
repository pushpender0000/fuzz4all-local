#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void createAndPrintStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    printf("%d\n", s.data);
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

void runTests(TestFunc func, int32_t vals[], uint8_t arr[][4], int count) {
    for (int i = 0; i < count; ++i) {
        func(vals[i], arr[i]);
    }
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){10 * i, initialArray};
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    createAndPrintStruct(x, y);
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%u\n", hashStruct(&s));
}

void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    runTests(func, vals, arr, sizeof(vals) / sizeof(vals[0]));
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunction);
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