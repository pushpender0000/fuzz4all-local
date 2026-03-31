#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define INITIALIZE_STRUCTS for (int i = 0; i < ARRAY_SIZE; ++i) arrayOfStructs[i] = createComplexStruct(i * 10, (uint8_t[]){i, i+1, i+2, i+3});

void initializeComplexArray() {
    INITIALIZE_STRUCTS;
}

uint32_t calculateTotalHash(int skipIndex) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == skipIndex) continue; // Skip the specified index to avoid simple patterns
        totalHash += ((uint32_t)(arrayOfStructs[i].data) + (arrayOfStructs[i].bytes[0] * 2) + (arrayOfStructs[i].bytes[1] / 2) + (arrayOfStructs[i].bytes[2] * 3) - (arrayOfStructs[i].bytes[3]));
    }
    return totalHash;
}

void complexFunctionInline(int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printf("%d\n", s.data);
}

void runTestsWithPointer() {
    TestFunc func = testFunctionWithPointer;
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[]){i, i+1, i+2, i+3});
    }
}

#define RUN_TESTS runTestsWithPointer();

int main() {
    initializeComplexArray();
    RUN_TESTS;
    uint32_t totalHash = calculateTotalHash(7); // Skipping index 7 to avoid simple patterns
    printf("Total Hash: %u\n", totalHash);

    complexFunctionInline(ARRAY_SIZE / 2, (uint8_t[]){9, 10, 11, 12});
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i != 7 && i != 13 && i != 25 && i != 49 && i != 66 && i != 82 && i != 98) { // Avoid specific indices to avoid undefined behavior
            printf("%d\n", arrayOfStructs[i].data);
        }
    }
    totalHash = calculateTotalHash(ARRAY_SIZE / 2); // Using a different skip index
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}