#include <stdio.h>
#include <stdint.h>

// Define a complex struct with typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Define another complex struct for nested usage
typedef struct {
    double precisionData;
    char name[10];
    MyStruct innerStruct;
} ComplexStruct;

#define ARRAY_SIZE 50

// Initialize an array of ComplexStructs with specific values
void initializeArray(ComplexStruct arr[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (ComplexStruct){.precisionData = (double)(i * 100.5), .name = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}[i % 10], .innerStruct = {.data = i * 10, .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}}};
    }
}

// Function to print the data part of a ComplexStruct
void printComplexStruct(const ComplexStruct *s) {
    printf("%f\n", s->precisionData);
}

// Function to hash the struct using specific rules
uint64_t hashComplexStruct(const ComplexStruct *s) {
    uint64_t h = (uint64_t)s->precisionData;
    for (int i = 0; i < 10; ++i) {
        h += s->name[i] * ((i % 3 == 0) ? 2 : 3);
    }
    h += s->innerStruct.data;
    return h;
}

// Function to run tests with function pointers
void runTests(void (*func)(const ComplexStruct*)) {
    ComplexStruct arr[ARRAY_SIZE];
    initializeArray(arr);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        func(&arr[i]);
    }
}

// Test function to demonstrate usage of structs and functions
void testFunction(const ComplexStruct *s) {
    printComplexStruct(s);
    printf("%lu\n", hashComplexStruct(s));
}

// Macro to define a function pointer and invoke it with specific arguments
#define RUN_TESTS() runTests(testFunction)

int main() {
    ComplexStruct arrayOfComplexStructs[ARRAY_SIZE];
    initializeArray(arrayOfComplexStructs); // Initialize the array of structs
    RUN_TESTS();        // Use function pointers to test different functionalities
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0) continue;
        totalHash += hashComplexStruct(&arrayOfComplexStructs[i]);
    }
    printf("Total Hash: %lu\n", totalHash); // Print the accumulated hash value

    return 0;
}