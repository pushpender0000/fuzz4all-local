#include <stdio.h>
#include <stdint.h>

// Define a struct with specific fields
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct from given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototype for the function pointer
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to print data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to initialize an array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        MyStruct s = CREATESTRUCT(10 * i, initialArray);
        printf("%d\n", s.data);
    }
}

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
}

// Main function to demonstrate functionality
int main() {
    initializeArray();
    runTests(testFunction);
    return 0;
}