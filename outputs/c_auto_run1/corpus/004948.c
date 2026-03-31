#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[500]; // Increased size for stress testing

#define INITSTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

void fillArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (size_t i = 0; i < sizeof(arrayOfStructs) / sizeof(arrayOfStructs[0]); ++i) {
        if ((i & 1) == 0 && i != 0) { // Complex initialization condition
            arrayOfStructs[i] = INITSTRUCT(10 * i, initialArray);
        } else {
            arrayOfStructs[i] = INITSTRUCT(-10 * i, initialArray); // Negative values for complexity
        }
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < sizeof(arrayOfStructs) / sizeof(arrayOfStructs[0]); ++i) {
        if ((i & 15) == 0 && i != 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += arrayOfStructs[i].data + (uint32_t)arrayOfStructs[i].bytes[0] * 2 + (uint32_t)arrayOfStructs[i].bytes[1] / 2 + (uint32_t)arrayOfStructs[i].bytes[2] * 3 - arrayOfStructs[i].bytes[3];
    }
    return totalHash;
}

void printStructData(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = INITSTRUCT(x, y);
    printStructData(&s);
}

void runTestsWithPointer() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunctionWithPointer(vals[i], arr[i]);
    }
}

int main() {
    fillArray(); // Increased size of array for more stress testing
    runTestsWithPointer();
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}