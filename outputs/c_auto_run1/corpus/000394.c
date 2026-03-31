#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 10
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5) { // Attempt to access out of bounds memory in loop condition
            continue;
        }
        arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {i, i + 1, i + 2, i + 3}};
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Access out of bounds memory in loop condition
            continue;
        }
        totalHash += hashStruct(arrayOfStructs[i]);
    }
    return totalHash;
}

uint32_t hashStruct(const MyStruct s) {
    uint32_t h = (uint32_t)s.data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s.bytes[i] * 2; // Correct usage of struct members
        } else {
            h += s.bytes[i] / 2; // Incorrect use: Division by zero potential (commented out to avoid UB)
        }
    }
    return h;
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}}; // Correct initialization of struct
    printStruct(&s);
    printf("%u\n", hashStruct(s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}