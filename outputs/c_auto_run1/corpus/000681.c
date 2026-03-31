#include <stdio.h>

typedef unsigned char uint8_t;
typedef signed int int32_t;
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 30
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i].data = 10 * i;
        for (int j = 0; j < 4; ++j) {
            arrayOfStructs[i].bytes[j] = (uint8_t)(1 + i * j);
        }
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 150, -150};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[4] = {(uint8_t)(i * 2), (uint8_t)(i * 3), (uint8_t)(i * 4), (uint8_t)(i * 5)};
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void stressTest() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);
}

int main() {
    stressTest();
    return 0;
}