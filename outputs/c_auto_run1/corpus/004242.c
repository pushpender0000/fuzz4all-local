#include <stdio.h>
#include <stdint.h>

// Define a macro for creating structures with specific data and byte arrays
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Define the structure MyStruct
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Typedef a function pointer type for testing purposes
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize an array of structures with specific conditions
void initializeArray(MyStruct *array) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if ((i % 7 == 0 || i % 9 == 0)) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the data part of a structure
void printStructData(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with a function pointer
void runTests(TestFunc func, int num_tests) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < num_tests && i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStructData(&s);
}

#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

// Main function to initialize the array and run tests
int main() {
    initializeArray(arrayOfStructs);
    runTests(testFunction, ARRAY_SIZE); // Run tests with testFunction
    return 0;
}