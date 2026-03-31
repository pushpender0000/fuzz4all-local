#include <stdio.h>
#include <stdint.h>

// Macro to define a struct with specific fields
#define DEFINE_STRUCT(name, type1, field1, type2, field2) \
typedef struct { \
    type1 field1; \
    type2 field2; \
} name##Struct; \
\
void initialize##name(int index, type1 val1, type2 val2) { \
    if (index >= 0 && index < ARRAY_SIZE) { \
        arrayOfStructs[index] = (name##Struct){val1, val2}; \
    } else { \
        printf("Index out of bounds\n"); \
    } \
} \
\
void print##name(const name##Struct *s) { \
    printf("%" #type1 "\n", s->field1); \
}

// Define a complex struct for testing
DEFINE_STRUCT(Complex, int32_t, data, uint8_t[4], bytes)

#define ARRAY_SIZE 50

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    ComplexStruct s = {x, y};
    printComplex(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

ComplexStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        initializeComplex(i, 10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printComplex(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    initializeComplex(ARRAY_SIZE / 2, 100 + 10 * (ARRAY_SIZE / 2), newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunction);
    printf("After second set of tests:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}