#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1000

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

#define INITIAL_VALUE 50
#define OFFSET_MULTIPLIER 17
#define BYTES_INITIALIZER {1, 2, 3, 4}

void initializeComplexArray(MyStruct array[]) {
    uint8_t initialBytes[4] = BYTES_INITIALIZER;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = createComplexStruct(INITIAL_VALUE + OFFSET_MULTIPLIER * i, initialBytes);
    }
}

uint32_t calculateTotalHash(const MyStruct array[]) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += ((uint32_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return totalHash;
}

void complexFunction(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFuncPtr)(MyStruct[], int32_t, uint8_t[]);

void runTestsWithPointer(TestFuncPtr func) {
    MyStruct array[ARRAY_SIZE];
    initializeComplexArray(array);
    uint8_t newBytes[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        func(array, i, newBytes[i % 4]);
    }
}

int main() {
    MyStruct array[ARRAY_SIZE];
    initializeComplexArray(array);
    runTestsWithPointer(complexFunction);
    uint32_t totalHash = calculateTotalHash(array);
    printf("Total Hash after stress: %u\n", totalHash);

    return 0;
}