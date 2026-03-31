#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024
#define HASH_FACTOR 379

typedef struct {
    int64_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

typedef void (*TestFuncPtr)(int64_t, uint8_t[4]);

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

#define INITIALIZE_STRUCTS initializeComplexArray()

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

uint64_t calculateTotalHash() {
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += ((uint64_t)(arrayOfStructs[i].data) + arrayOfStructs[i].bytes[0] * 2 + arrayOfStructs[i].bytes[1] / 2 + arrayOfStructs[i].bytes[2] * 3 - arrayOfStructs[i].bytes[3]);
    }
    return totalHash;
}

void testFunctionWithPointer(int64_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", ((uint64_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

void complexFunction(MyStruct array[], int64_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        complexFunction(arrayOfStructs, i, newBytes);
    }
}

int main() {
    INITIALIZE_STRUCTS;
    runTestsWithPointer(testFunctionWithPointer);
    uint64_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %lu\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    stressTest();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after stressTest: %lu\n", totalHash);

    return 0;
}