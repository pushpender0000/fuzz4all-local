#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray() {
    static uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i * i + 7) % 13 == 0) { // Complex condition to avoid simple patterns
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i * i + 7) % 13 == 0) { // Complex condition to avoid simple patterns
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i * i + 7) % 3 == 0) { // Complex condition to avoid simple patterns
            continue;
        }
        totalHash += arrayOfStructs[i].data;
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printf("%d\n", s.data);
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
        if ((i * i + 7) % 13 == 0) { // Complex condition to avoid simple patterns
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

MyStruct arrayOfStructs[ARRAY_SIZE];

int main() {
    initializeArray();
    runTestsWithPointer(testFunctionWithPointer);
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