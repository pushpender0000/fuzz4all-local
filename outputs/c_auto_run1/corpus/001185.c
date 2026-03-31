#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[20];

void initializeArray() {
    for (int i = 0; i < 20; ++i) {
        if (i != 5 && i != 10) { // Ensure no index 5 and no index 10 are initialized differently
            arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {1, 2, 3, 4}};
        } else if (i == 10) { // Special case for index 10 to ensure it's handled correctly
            arrayOfStructs[i] = (MyStruct){.data = -10 * i, .bytes = {5, 6, 7, 8}};
        }
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2; // Ensure multiplication and division are used correctly
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data); // Print the data field of the struct
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

#define ARRAY_SIZE 20

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){1, 2, 3, 4}); // Ensure function pointers are used correctly with parameters
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}}; // Ensure initialization is correct
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}}; // Ensure complex function handles bounds checking correctly
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Ensure loop skips certain elements based on condition
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash); // Print the computed total hash

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break; // Ensure loop breaks at a specific condition
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Ensure loop skips certain elements based on condition
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash); // Print the updated total hash after modifications

    return 0;
}