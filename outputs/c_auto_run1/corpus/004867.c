#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void createComplexStruct(MyStruct array[], int index, int32_t val, const uint8_t arr[]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        array[index] = (MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}};
    } else {
        printf("Index out of bounds\n");
    }
}

void printStruct(const MyStruct *s) {
    if (s != NULL) {
        printf("%d\n", s->data);
    }
}

#define INITIALIZE_ARRAY for (int i = 0; i < ARRAY_SIZE; ++i) {\
                            createComplexStruct(arrayOfStructs, i, (10 * i), initialArray);\
                        }

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    INITIALIZE_ARRAY;
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += ((uint32_t)(arrayOfStructs[i].data) + arrayOfStructs[i].bytes[0] * 2 + arrayOfStructs[i].bytes[1] / 2 + arrayOfStructs[i].bytes[2] * 3 - arrayOfStructs[i].bytes[3]);
    }
    return totalHash;
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", ((uint32_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        createComplexStruct(arrayOfStructs, i, 100 + 10 * i, newBytes);
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    stressTest();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after stressTest: %u\n", totalHash);

    return 0;
}