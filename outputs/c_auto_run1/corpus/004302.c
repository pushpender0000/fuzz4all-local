#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int64_t, uint8_t[4]);

MyStruct createComplexStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

static inline void complexFunctionInline(MyStruct array[], int64_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

MyStruct* initializeComplexArray() {
    MyStruct *arrayOfStructs = (MyStruct*)malloc(ARRAY_SIZE * sizeof(MyStruct));
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
    return arrayOfStructs;
}

uint32_t calculateTotalHash(MyStruct* array) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += ((uint32_t)(array[i].data) + (array[i].bytes[0] * 2) + (array[i].bytes[1] / 2) + (array[i].bytes[2] * 3 - array[i].bytes[3]));
    }
    return totalHash;
}

void testFunctionWithPointer(int64_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", ((uint32_t)(s.data) + (s.bytes[0] * 2) + (s.bytes[1] / 2) + (s.bytes[2] * 3 - s.bytes[3])));
}

typedef void (*TestFuncPtr)(int64_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printComplexArray(MyStruct* array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&array[i]);
    }
}

int main() {
    MyStruct* arrayOfStructs = initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunctionInline(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printComplexArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash: %u\n", totalHash);

    free(arrayOfStructs); // Free allocated memory
    return 0;
}