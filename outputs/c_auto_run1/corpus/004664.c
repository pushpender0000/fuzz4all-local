#include <stdio.h>
#include <stdint.h>

// Macro to create a complex struct with multiple operations
#define CREATESTRUCT(val) ((MyStruct){val, {val + 10, val * 2, (uint8_t)(val - 3), (uint8_t)(val ^ 4)}})

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to perform a series of complex operations on the struct and print it
void testFunction(MyStruct s, uint8_t arr[]) {
    printf("%d\n", s.data);
    for (int i = 0; i < 4; ++i) {
        printf("%u ", s.bytes[i]);
    }
    printf("\n");
}

typedef void (*TestFunc)(MyStruct, uint8_t[]);

// Function to initialize an array of structs with complex conditions
void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        MyStruct s = CREATESTRUCT(10 * i);
        printf("%d\n", s.data);
    }
}

#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to fill the array with complex structs and perform operations on it
void fillArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns and potential UB
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i);
    }
}

// Function to test the function pointer usage with complex parameters
void runTests(TestFunc func) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns and potential UB
            continue;
        }
        uint8_t arr[] = {1, 2, 3, 4};
        func(arrayOfStructs[i], arr);
    }
}

// Function to calculate the total hash of all structs in the array with complex conditions including undefined behavior (accessing out of bounds)
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns and potential UB
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to perform a complex operation with an offset and new bytes including undefined behavior (accessing out of bounds)
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATESTRUCT(100 + 10 * offset);
        printf("Updated struct at offset %d\n", offset);
    } else {
        printf("Offset out of bounds\n");
    }
}

int main() {
    initializeArray();
    fillArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    runTests(testFunction);
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}