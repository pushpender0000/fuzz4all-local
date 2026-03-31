#include <stdio.h>
#include <stdint.h>

// Define constants and types
#define ARRAY_SIZE 100
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a new struct instance
#define CREATE_STRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototypes
uint32_t hashStruct(const MyStruct *s);
void printStruct(const MyStruct *s);
void initializeArray(MyStruct array[]);
void processArray();
void complexFunction(int32_t offset, uint8_t newBytes[4]);
typedef void (*TestFunc)(int32_t, uint8_t[4]);
void runTests(TestFunc func);
void testFunction(int32_t x, uint8_t y[4]);
uint32_t calculateTotalHash();

// Global array of structs
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array with complex data
void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATE_STRUCT(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
}

// Function to print the contents of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to calculate the hash of a struct
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

// Function to process the array of structs
void processArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to perform a complex manipulation of the array by struct at given offset
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATE_STRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to run tests using a function pointer
typedef void (*TestFunc)(int32_t, uint8_t[4]);
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the creation and printing of a struct
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATE_STRUCT(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Main function to initialize the array and run tests
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    processArray();
    totalHash = calculateTotalHash(); // Use the new function to increase complexity
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}