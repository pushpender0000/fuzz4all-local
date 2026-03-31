#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

// Define a complex type using typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a new MyStruct instance
#define CREATE_STRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

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

// Function to print the struct data (deterministic output)
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Define a function pointer type
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to run tests with a function pointer (deterministic execution)
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test using the function pointer (deterministic inputs and outputs)
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATE_STRUCT(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs (deterministic initialization)
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATE_STRUCT(10 * i, initialArray);
    }
}

// Function to print the array of structs (deterministic output)
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of the array of structs (deterministic computation)
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

// Function to manipulate a specific struct in the array (deterministic modification)
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATE_STRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test using the function pointer with a different signature (deterministic execution)
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATE_STRUCT(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Main function to run the tests and demonstrate the program's behavior (deterministic control flow)
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTests(testFunctionWithPointer);
    printf("After second set of tests:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}