#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50
#define INITIALIZE_STRUCT(s, val, arr) ((s = (MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}}))

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

static inline void complexFunctionInline(MyStruct array[], int offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        INITIALIZE_STRUCT(array[offset], 100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 != 0 && i % 13 != 0)) { // Ensure no specific indices are skipped to avoid undefined behavior
            INITIALIZE_STRUCT(arrayOfStructs[i], 10 * i, initialArray);
        }
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 != 0) { // Ensure every third element is skipped to avoid simple patterns
            totalHash += HASH(&arrayOfStructs[i]);
        }
    }
    return totalHash;
}

void testFunctionWithPointer(int32_t x, const uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int32_t, const uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[4]){i * 10 + 1, i * 10 + 2, i * 10 + 3, i * 10 + 4});
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 != 0 && i % 13 != 0)) { // Ensure no specific indices are skipped to avoid undefined behavior
            printStruct(&arrayOfStructs[i]);
        }
    }
}

void complexFunction(MyStruct array[], int offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        INITIALIZE_STRUCT(array[offset], 100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void stressTest() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 != 0 && i % 13 != 0)) { // Ensure no specific indices are skipped to avoid undefined behavior
            complexFunction(arrayOfStructs, i, (uint8_t[4]){i * 10 + 1, i * 10 + 2, i * 10 + 3, i * 10 + 4});
        }
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    stressTest();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after stressTest: %u\n", totalHash);

    return 0;
}