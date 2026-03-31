#include <stdio.h>
#include <stdint.h>

// Define a complex calculation macro using struct fields
#define COMPLEX_CALC(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Typedef for a function pointer type
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to create a struct with given values
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function array for testing function pointer usage
void (*funcArray[])(int32_t, uint8_t[4]) = {&printStruct};

// Main function to test the function pointer usage
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage with an array of structs
void testFunctionPointerUsage() {
    MyStruct arrayOfStructs[4] = {
        createStruct(10, (uint8_t[]){1, 2, 3, 4}),
        createStruct(-10, (uint8_t[]){5, 6, 7, 8}),
        createStruct(300, (uint8_t[]){9, 10, 11, 12}),
        createStruct(-300, (uint8_t[]){13, 14, 15, 16})
    };
    for (int i = 0; i < sizeof(arrayOfStructs) / sizeof(arrayOfStructs[0]); ++i) {
        funcArray[0](&arrayOfStructs[i]); // Using the function pointer array
        printf("%u\n", COMPLEX_CALC(&arrayOfStructs[i]));
    }
}

int main() {
    runTests(printStruct);
    testFunctionPointerUsage();
    return 0;
}