#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

// Macro to calculate the hash of a complex struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a complex struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to print the data part of a complex struct
void printComplexStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with function pointers and complex operations
void runTestsWithPointerAndMacro(TestFunc func, int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        MyStruct s = CREATESTRUCT(100 + 10 * offset, newBytes);
        printComplexStruct(&s);
        printf("%u\n", HASH(&s));
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to initialize the array of complex structs with specific conditions
void initializeArrayWithSpecificConditions() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        MyStruct s = CREATESTRUCT(10 * i, initialArray);
        printComplexStruct(&s);
    }
}

// Function to test the function pointer usage with complex operations and macros
void testFunctionWithPointerAndMacro() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        runTestsWithPointerAndMacro(testFunctionWithPointerAndMacro, i, newBytes);
    }
}

// Function to demonstrate function pointer usage with a more complex scenario
void demonstrateFunctionPointers() {
    TestFunc func = testFunctionWithPointerAndMacro;
    uint8_t newBytes[] = {13, 14, 15, 16};
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        runTestsWithPointerAndMacro(func, i, newBytes);
    }
}

// Main function to initialize and demonstrate the usage of structs, macros, and function pointers
int main() {
    initializeArrayWithSpecificConditions();
    testFunctionWithPointerAndMacro();
    demonstrateFunctionPointers();
    return 0;
}