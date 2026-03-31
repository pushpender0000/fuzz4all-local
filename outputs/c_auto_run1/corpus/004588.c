#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 50
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct *array);
uint32_t calculateTotalHash(const MyStruct *array, size_t size);
void complexFunction(MyStruct *array, int offset, const uint8_t newBytes[4]);
void printStruct(const MyStruct *s);
void runTests(TestFunc func);

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);

    printf("Initial Array:\n");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }

    uint32_t initialHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Initial Total Hash: %u\n", initialHash);

    // Perform a complex operation on the array
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);

    printf("After complex function call:\n");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }

    uint32_t updatedHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Updated Total Hash: %u\n", updatedHash);

    // Test function pointer usage
    runTests(testFunction);

    return 0;
}

void initializeArray(MyStruct *array) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = (MyStruct){10 * i, {initialArray[0], initialArray[1], initialArray[2], initialArray[3]}};
    }
}

uint32_t calculateTotalHash(const MyStruct *array, size_t size) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < size; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += array[i].data + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3];
    }
    return totalHash;
}

void complexFunction(MyStruct *array, int offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", (uint32_t)(s.data + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}