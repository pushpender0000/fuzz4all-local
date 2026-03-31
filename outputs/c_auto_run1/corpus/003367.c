#include <stdio.h>

// Define a simple struct
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a new struct instance
#define NEW_STRUCT(val, arr) ((MyStruct){(val), {(arr)[0], (arr)[1], (arr)[2], (arr)[3]}})

// Function to print the contents of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Inline function to calculate hash (simple implementation for demonstration)
static inline uint32_t hashStruct(const MyStruct *s) {
    return (uint32_t)(s->data) + 4*(s->bytes[0] & 15); // Basic hash based on data and bytes
}

// Function pointer type definition
typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

// Function to initialize an array of structs
void initializeArray(MyStruct *array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue; // Skip some elements to avoid UB or trivial cases
        }
        array[i] = NEW_STRUCT(10 * i, (uint8_t[]){1, 2, 3, 4});
    }
}

// Function to calculate total hash of the structs in an array
uint32_t calculateTotalHash(const MyStruct *array) {
    uint32_t total = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue; // Skip every third element to introduce more complexity
        }
        total += hashStruct(&array[i]);
    }
    return total;
}

// Function to test a function through function pointers
void runTests(TestFuncPtr func, MyStruct *array) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (uint8_t[]){1, 2, 3, 4}); // Fixed array for consistency
    }
}

// Main function to demonstrate the usage of structs and function pointers
int main() {
    const int ARRAY_SIZE = 100;
    MyStruct array[ARRAY_SIZE];
    initializeArray(array);

    runTests(testFunction, array); // Using testFunction defined below
    uint32_t totalHash = calculateTotalHash(array);
    printf("Total Hash: %u\n", totalHash);

    return 0;
}

// Test function to be used with the function pointer
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = NEW_STRUCT(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}