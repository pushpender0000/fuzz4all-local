#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 50

// Macro to calculate the hash of a struct with complex operations
#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 - (s)->bytes[1] / 3 + (s)->bytes[2] * 4 ^ (s)->bytes[3])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values, including complex operations
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0] + 1, arr[1] * 2, arr[2] - 3, arr[3] ^ 4}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to initialize the array of structs with given values and complex conditions
void initializeArray(MyStruct *array) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the data part of a struct with complex formatting
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to test the function pointer usage with complex parameters
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to calculate the total hash of all structs in the array with complex conditions
uint32_t calculateTotalHash(const MyStruct *array) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns and potential UB
            continue;
        }
        totalHash += HASH(&array[i]);
    }
    return totalHash;
}

// Function to perform a complex operation with an offset and new bytes including undefined behavior (accessing out of bounds)
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunction(vals[i], arr[i]);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray(arrayOfStructs);
    runTests();
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}