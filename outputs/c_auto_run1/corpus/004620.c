#include <stdio.h>
#include <stdint.h>

// Define complex structs using typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a structure instance
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Function prototypes
void printStructData(const MyStruct *s);
uint32_t calculateTotalHash(MyStruct arrayOfStructs[], int size);
void runTestsWithPointer(void (*func)(int32_t, uint8_t[4]));

#define ARRAY_SIZE 150
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structures
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the data field of a structure
void printStructData(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function pointer type definition
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Test function that uses the function pointer
void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStructData(&s);
}

// Function to run tests with a function pointer and complex manipulation
void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Main function to initialize the array and run tests with a function pointer
int main() {
    initializeArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Total Hash: %u\n", totalHash);
    return 0;
}

// Function to calculate the total hash of the data field in the structures
uint32_t calculateTotalHash(MyStruct arrayOfStructs[], int size) {
    uint32_t totalHash = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        totalHash += ((uint32_t)(&arrayOfStructs[i])->data + (&arrayOfStructs[i])->bytes[0] * 2 + (&arrayOfStructs[i])->bytes[1] / 2 + (&arrayOfStructs[i])->bytes[2] * 3 - (&arrayOfStructs[i])->bytes[3]);
    }
    return totalHash;
}