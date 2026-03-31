#include <stdio.h>
#include <stdint.h>

// Define a simple structure
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to calculate the size of an array at compile time
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Function prototypes
MyStruct createStruct(int32_t val, const uint8_t arr[]);
uint32_t hashStruct(const MyStruct *s);
void printStruct(const MyStruct *s);
void runTests(void (*func)(int32_t, const uint8_t[4]));
void testFunction(int32_t x, const uint8_t y[4]);

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray();
void printArray();
uint32_t calculateTotalHash();
void complexFunction(int32_t offset, const uint8_t newBytes[4]);
void stressTest();

// Function to create a struct
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val};
    for (uint8_t i = 0; i < ARRAY_SIZE(s.bytes); ++i) {
        s.bytes[i] = arr[i];
    }
    return s;
}

// Function to calculate the hash of a struct
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (uint8_t i = 0; i < ARRAY_SIZE(s->bytes); ++i) {
        h += s->bytes[i];
    }
    return h;
}

// Function to print the data of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with function pointer
void runTests(void (*func)(int32_t, const uint8_t[4])) {
    int32_t vals[] = {10, -10, 150, -150};
    const uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (uint8_t i = 0; i < ARRAY_SIZE(vals); ++i) {
        func(vals[i], arr[i]);
    }
}

// Test function implementation
void testFunction(int32_t x, const uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Function to initialize the array of structs
void initializeArray() {
    const uint8_t initialArray[] = {1, 2, 3, 4};
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

// Function to print the entire array of structs
void printArray() {
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of all structs in the array
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to modify a specific struct in the array
void complexFunction(int32_t offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Stress test function to exercise all functionalities
void stressTest() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    const uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);
}

int main() {
    stressTest();
    return 0;
}