#include <stdio.h>
#include <stdint.h>

typedef uint32_t HashType;

struct ComplexStruct {
    int32_t data;
    uint8_t bytes[4];
};

#define ARRAY_SIZE 100

void createComplexStruct(struct ComplexStruct *s, int32_t val, const uint8_t arr[]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

void printStruct(const struct ComplexStruct *s) {
    printf("%d\n", s->data);
}

#define HASH(s) ((HashType)(((s)->data * 2 + (s)->bytes[0]) * 3 - (s)->bytes[1] / 4))

typedef void (*TestFuncPtr)(int32_t, uint8_t*);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    struct ComplexStruct s;
    createComplexStruct(&s, x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

struct ComplexStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 13 == 0) && i != 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        createComplexStruct(&arrayOfStructs[i], 10 * i, initialArray);
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

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        createComplexStruct(&arrayOfStructs[offset], 100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 13 == 0) && i != 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

void initializeArrayWithRandomValues() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        uint8_t bytes[] = {i % 256, (i + 1) % 256, (i + 2) % 256, (i + 3) % 256};
        createComplexStruct(&arrayOfStructs[i], 10 * i, bytes);
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printComplexArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // New function to initialize array with random values for testing
    initializeArrayWithRandomValues();
    printf("After initializing array with random values:\n");
    printComplexArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after random initialization: %u\n", totalHash);

    return 0;
}