#include <stdio.h>
#include <stdint.h>

// Define a complex struct with nested members
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a new instance of MyStruct for easy initialization
#define NEW_STRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function to hash the struct's data and bytes using complex operations
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * ((i + 1) * 2); // Increase complexity by adding more operations
        } else {
            h -= s->bytes[i] / ((i + 1) * 2); // Decrease complexity for even less defined behavior
        }
    }
    return h;
}

// Function pointer type definition
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Test function that uses the MyStruct and prints its hash
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = NEW_STRUCT(x, y);
    printf("%u\n", hashStruct(&s));
}

#define ARRAY_SIZE 150
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = NEW_STRUCT(10 * i, initialArray);
    }
}

// Function to calculate the total hash of the structs in the array
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Main function to demonstrate the program's functionality
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}