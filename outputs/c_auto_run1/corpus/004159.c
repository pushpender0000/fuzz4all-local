#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100
#define HASH(x) ((uint32_t)(x)->data + (x)->bytes[0] * 2 + (x)->bytes[1] / 2 + (x)->bytes[2] * 3 - (x)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(MyStruct*, int);

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

static inline void complexFunctionInline(MyStruct array[], int index, uint8_t newBytes[4]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        array[index] = createComplexStruct(100 + 10 * index, newBytes);
    } else {
        printf("Index out of bounds\n");
    }
}

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

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

void testFunctionWithPointer(MyStruct array[], int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        complexFunctionInline(array, offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTestsWithPointer(TestFunc func) {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = -5; i < ARRAY_SIZE + 5; ++i) { // Test with out-of-bound indices
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        func(arrayOfStructs, i, newBytes);
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

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    return 0;
}