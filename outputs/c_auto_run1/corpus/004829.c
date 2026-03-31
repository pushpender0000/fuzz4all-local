#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef uint32_t HashType;

typedef struct {
    int64_t data;
    uint8_t bytes[8];
} MyStruct;

MyStruct createComplexStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

#define HASH(s) ((HashType)(((s)->data * 2 + (s)->bytes[0]) * 3 - (s)->bytes[1] / 4))

typedef void (*TestFuncPtr)(int64_t, uint8_t*);

void runTestsWithPointer(TestFuncPtr func) {
    int64_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i % 2]);
    }
}

void testFunctionWithPointer(int64_t x, uint8_t y[8]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4, 5, 6, 7, 8};
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

void complexFunction(int64_t offset, uint8_t newBytes[8]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
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

void initializeArrayWithRandomValues() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createComplexStruct(10 * i, (uint8_t[]){i % 256, (i + 1) % 256, (i + 2) % 256, (i + 3) % 256, (i + 4) % 256, (i + 5) % 256, (i + 6) % 256, (i + 7) % 256});
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12, 13, 14, 15, 16};
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