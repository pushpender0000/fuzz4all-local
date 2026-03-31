#include <stdio.h>
#include <stdint.h>

// Macro to calculate the size of an array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Define a struct with nested structure and typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to create a MyStruct instance
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to hash the struct
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

// Function to print the struct data
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Typedef for a function pointer type TestFunc
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < ARRAY_SIZE(vals); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Define an array of structs
#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with specific patterns
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

// Function to print the structs in the array
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Main function to demonstrate the usage of structs and function pointers
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);
    return 0;
}