#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1]}})

typedef struct {
    int32_t data;
    uint8_t bytes[2];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[2]);

MyStruct arrayOfStructs[ARRAY_SIZE];

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = CREATESTRUCT(10 * i, (uint8_t[]){i, i + 1});
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += ((uint32_t)(&arrayOfStructs[i])->data + (&arrayOfStructs[i])->bytes[0] * 2 + (&arrayOfStructs[i])->bytes[1]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[2]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[2]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[2]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][2] = {{1, 2}, {5, 6}, {9, 10}, {13, 14}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
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
    uint8_t newBytes[] = {9, 10};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}