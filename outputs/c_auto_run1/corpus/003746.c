#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

// Macro to calculate the hash of a struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

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
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

// Function to perform a complex operation with an offset and new bytes
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to print the structs in the array with complex conditions
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to perform a series of complex operations using function pointers
void runComplexOperations(TestFunc func) {
    int32_t offsets[] = {1, 2, 3, 4};
    uint8_t newBytes[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); ++i) {
        func(offsets[i], newBytes[i]);
    }
}

// Main function to execute the program logic
int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Perform complex operations using function pointers
    runComplexOperations(complexFunction);
    printf("After complex operations:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after complex operations: %u\n", totalHash);

    return 0;
}