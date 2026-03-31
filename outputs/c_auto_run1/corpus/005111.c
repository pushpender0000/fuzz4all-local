#include <stdio.h>
#include <stdint.h>

// Macro for calculating factorial using recursion
#define FACTORIAL(n) ((n) > 1 ? (n) * FACTORIAL((n) - 1) : 1)

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to create a complex struct
MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Macro to calculate a simple hash function for demonstration
#define HASH_STRUCT(s) ((uint64_t)(s.data) + (s.bytes[0] * 2) + (s.bytes[1] / 2) + (s.bytes[2] * 3) - s.bytes[3])

// Function pointer type definition for clarity
typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

// Function to use the function pointer with a struct instance
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", HASH_STRUCT(s));
}

// Function to run tests with a function pointer
void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, 20, 30, 40};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Main function to stress the GCC compiler with complex usage of structs and function pointers
int main() {
    runTestsWithPointer(testFunctionWithPointer);
    return 0;
}