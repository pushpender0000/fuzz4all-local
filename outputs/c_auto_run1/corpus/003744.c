#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

// Macro to calculate the hash of a struct
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototypes
void printStruct(const MyStruct *s);
uint32_t calculateHash(const MyStruct *s);
void runTests();
void complexFunction(int32_t offset, uint8_t newBytes[4]);
typedef void (*TestFunc)(int32_t, uint8_t[4]);
void testFunctionPointer(TestFunc func);

// Function to initialize the array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
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
        totalHash += calculateHash(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function implementation
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t calculateHash(const MyStruct *s) {
    return HASH(s);
}

void runTests() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunctionPointer(&testFunction);
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void testFunctionPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

MyStruct arrayOfStructs[ARRAY_SIZE];

int main() {
    initializeArray();
    runTests();
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}