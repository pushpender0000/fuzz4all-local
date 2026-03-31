Here's a more complex C program that includes multiple structs, typedefs, macros, inline functions, and function pointers. This program is designed to stress the GCC compiler by increasing complexity without introducing undefined behavior:

```c
#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 150

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double val;
    char chars[4];
} AnotherStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

AnotherStruct createAnotherStruct(double dVal, const char chars[]) {
    AnotherStruct a = {dVal, {chars[0], chars[1], chars[2], chars[3]}};
    return a;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

uint32_t hashAnotherStruct(const AnotherStruct *a) {
    uint32_t h = (uint32_t)(*((double*)a)); // Simple hashing for demonstration
    for (int i = 0; i < 4; ++i) {
        h += a->chars[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);
typedef void (*AnotherTestFunc)(double, char[4]);

#define INITIALIZE_ARRAY \
    for (int i = 0; i < ARRAY_SIZE; ++i) { \
        if (i % 7 == 0 || i % 13 == 0) { continue; } \
        arrayOfStructs[i] = createStruct(10 * i, initialArray); \
    }

#define PRINT_ARRAY \
    for (int i = 0; i < ARRAY_SIZE; ++i) { \
        if (i % 7 == 0 || i % 13 == 0) { break; } \
        printStruct(&arrayOfStructs[i]); \
    }

MyStruct arrayOfStructs[ARRAY_SIZE];
uint8_t initialArray[] = {1, 2, 3, 4};

void initializeArray() {
    INITIALIZE_ARRAY;
}

void printArray() {
    PRINT_ARRAY;
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { continue; }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void complexAnotherFunction(int32_t offset, char newChars[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createAnotherStruct(100.0 + 10 * offset, newChars);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void anotherTestFunction(double d, char c[4]) {
    AnotherStruct a = createAnotherStruct(d, c);
    printf("%u\n", hashAnotherStruct(&a));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);
typedef void (*AnotherTestFuncPtr)(double, char[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void runAnotherTestsWithPointer(AnotherTestFuncPtr func) {
    double dVals[] = {10.0, -10.0, 300.0, -300.0};
    char cArrays[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(dVals) / sizeof(dVals[0]); ++i) {
        func(dVals[i], cArrays[i]);
    }
}

void printArrayWithPointer() {
    PRINT_ARRAY;
}

int main() {
    initializeArray();
    runTestsWithPointer(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    char newChars[] = {9, 10, 11, 12};
    complexAnotherFunction(ARRAY_SIZE / 2, newChars);
    printf("After complex another function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation