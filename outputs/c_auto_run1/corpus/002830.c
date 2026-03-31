#include <stdio.h>
#include <stdint.h>

// Macro to calculate the size of an array for a given struct
#define ARRAY_SIZE(s) (sizeof(s) / sizeof(*s))

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to create a struct from given values
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to print the data part of a struct
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Macro to calculate a simple hash based on struct members
#define HASH_STRUCT(s) ((uint32_t)(s.data + s.bytes[0] + s.bytes[1] + s.bytes[2] + s.bytes[3]))

// Function to run tests with function pointers
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
    printf("%u\n", HASH_STRUCT(s));
}

// Array of structs to be used in tests
MyStruct arrayOfStructs[100];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 100; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < 100; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < 100; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH_STRUCT(arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    return 0;
}