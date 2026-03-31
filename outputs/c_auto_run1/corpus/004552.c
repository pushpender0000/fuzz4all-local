#include <stdio.h>
#include <stdint.h>

// Define a struct with typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct instance
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Define the array size and initialize it with complex conditions
#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with specific values
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function using function pointers for deterministic testing
void testFunctionPointer() {
    typedef void (*TestFunc)(int32_t, uint8_t[4]);
    TestFunc func = (TestFunc)printStruct; // Cast to match the function pointer type
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(CREATESTRUCT(vals[i], {1, 2, 3, 4}));
    }
}

// Main function to execute the tests and stress GCC
int main() {
    initializeArray();
    testFunctionPointer();

    // Print a specific struct from the array
    int index = ARRAY_SIZE / 2;
    if (index < ARRAY_SIZE && index % 3 != 0) { // Ensure it's within bounds and not skipped by complex condition
        printStruct(&arrayOfStructs[index]);
    } else {
        printf("Index out of range or skipped.\n");
    }

    return 0;
}