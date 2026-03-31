#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double complexVal;
    uint64_t largeNumber;
} ComplexType;

#define INITIALIZE_STRUCT(index, val) ((MyStruct){val, {(uint8_t)(index), (uint8_t)(index + 1), (uint8_t)(index + 2), (uint8_t)(index + 3)}})

void initializeArrayWithComplexType() {
    ComplexType complexTypes[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        complexTypes[i] = (ComplexType){.complexVal = (double)i * 1.234, .largeNumber = (uint64_t)i << 32};
    }
}

void manipulateStructArray(MyStruct array[], uint8_t val) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = INITIALIZE_STRUCT(i, (int32_t)(val + i));
    }
}

void printStructs() {
    MyStruct array[ARRAY_SIZE];
    manipulateStructArray(array, 10); // Example of parameter manipulation
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        printf("%d\n", array[i].data);
    }
}

typedef void (*FuncPtr)(uint8_t, int32_t);

void complexFunction(uint8_t a, int32_t b) {
    MyStruct s = INITIALIZE_STRUCT(a, b);
    printf("%d\n", s.data);
}

void runTestsWithPointer() {
    FuncPtr func = complexFunction;
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        func(i, (int32_t)(i * 3));
    }
}

uint64_t calculateTotalHash() {
    uint64_t totalHash = 0;
    MyStruct array[ARRAY_SIZE];
    manipulateStructArray(array, 10); // Example of parameter manipulation
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += ((uint64_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return totalHash;
}

int main() {
    initializeArrayWithComplexType();
    runTestsWithPointer();
    uint64_t totalHash = calculateTotalHash();
    printf("Total Hash: %lu\n", totalHash);
    printStructs(); // Additional function to test multiple outputs and control flow
    return 0;
}