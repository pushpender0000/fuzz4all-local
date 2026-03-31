#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 500
MyStruct arrayOfStructs[ARRAY_SIZE];

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i & 1) == 0 && i != 0) {
            arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
        } else {
            arrayOfStructs[i] = CREATESTRUCT(-10 * i, initialArray);
        }
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i & 15) == 0 && i != 0) {
            continue;
        }
        totalHash += ((uint32_t)(&arrayOfStructs[i])->data + (&arrayOfStructs[i])->bytes[0] * 2 + (&arrayOfStructs[i])->bytes[1] / 2 + (&arrayOfStructs[i])->bytes[2] * 3 - (&arrayOfStructs[i])->bytes[3]);
    }
    return totalHash;
}

void printStructData(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStructData(&s);
}

void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}