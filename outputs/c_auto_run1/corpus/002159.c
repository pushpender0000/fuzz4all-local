#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to create a struct instance
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define HASH_STRUCT(s) ({ \
    uint32_t h = (uint32_t)(s)->data; \
    for (int i = 0; i < 4; ++i) { \
        if (i % 2 == 0) { \
            h += (s)->bytes[i] * 2; \
        } else { \
            h += (s)->bytes[i] / 2; \
        } \
    } \
    h; \
})

// Macro to calculate hash for the struct
#define HASH_STRUCT_V2(s) ({ \
    uint32_t h = (uint32_t)(s)->data + ((s)->bytes[0] * 3); \
    h += (s)->bytes[1] << 1; \
    h -= (s)->bytes[2] >> 1; \
    h *= (s)->bytes[3]; \
    h; \
})

// Function to print struct data
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to initialize the array of structs with specific conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

// Function to print the first few elements of the array
void printArray() {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) { // Print only half of the array
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate total hash using HASH_STRUCT macro
uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += HASH_STRUCT(&arrayOfStructs[i]);
    }
    return totalHash;
}

// Function to modify a specific struct in the array (stress test for pointer manipulation)
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to test function using a function pointer (stress test for function pointers)
void runTestsWithPointer(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", HASH_STRUCT(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

// Main function to demonstrate the usage of complexFunction and testFunction through a function pointer
int main() {
    initializeArray();
    runTestsWithPointer(testFunction); // Use function pointer to call testFunction
    printf("Total Hash: %u\n", calculateTotalHash());

    // Additional stress test for complex function and array manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    printf("Updated Total Hash: %u\n", calculateTotalHash());

    return 0;
}