#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize an array of structs with complex conditions
void initializeArray(MyStruct *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = CREATESTRUCT(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with a function pointer
void runTests(TestFunc func, size_t size) {
    int32_t vals[] = {10, -10, 300, -300};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

// Function to test the function pointer usage
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
}

MyStruct arrayOfStructs[50];

// Main function to demonstrate the program
int main() {
    initializeArray(arrayOfStructs, 50);
    runTests(testFunction, 50);
    return 0;
}