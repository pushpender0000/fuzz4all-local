#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct array[]);
uint32_t calculateTotalHash(const MyStruct array[], size_t size);
void printStruct(const MyStruct *s);
void complexFunction(MyStruct array[], int offset, const uint8_t newBytes[4]);
void runTests(TestFunc func);

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Total Hash: %u\n", totalHash);

    // Complex function call to stress memory manipulation and type handling
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}

void initializeArray(MyStruct array[]) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        array[i] = (MyStruct){.data = 10 * i, .bytes = {initialArray[0], initialArray[1], initialArray[2], initialArray[3]}};
    }
}

uint32_t calculateTotalHash(const MyStruct array[], size_t size) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < size; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += ((uint32_t)array[i].data + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return totalHash;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void complexFunction(MyStruct array[], int offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
}