#include <stdio.h>
#include <stdint.h>

// Define a complex struct with nested types
typedef struct {
    int32_t data;
    uint16_t id;
} SimpleStruct;

typedef struct {
    SimpleStruct *elements;
    size_t count;
} ComplexArray;

#define MAX_COMPLEX 50

// Initialize the complex array with a macro
#define INIT_COMPLEX_ARRAY(arr) \
    do { \
        for (size_t i = 0; i < MAX_COMPLEX; ++i) { \
            arr[i].data = (int32_t)(i * 10); \
            arr[i].id = (uint16_t)(i * 20); \
        } \
    } while(0);

// Function to calculate a hash value for SimpleStruct elements
uint32_t calcHash(const SimpleStruct *s) {
    return (uint32_t)(s->data + s->id);
}

// Function to print the sum of hashes from the complex array
void printSumOfHashes(ComplexArray ca) {
    uint32_t totalSum = 0;
    for (size_t i = 0; i < ca.count; ++i) {
        totalSum += calcHash(&ca.elements[i]);
    }
    printf("%u\n", totalSum);
}

// Function pointer usage
void (*printFuncPtr)(void) = printSumOfHashes;

int main() {
    ComplexArray ca;
    ca.count = MAX_COMPLEX;
    ca.elements = (SimpleStruct *)malloc(MAX_COMPLEX * sizeof(SimpleStruct));
    
    INIT_COMPLEX_ARRAY(ca.elements); // Initialize the complex array

    printFuncPtr(); // Call the function pointer to trigger the hash sum calculation and printing

    free(ca.elements); // Free allocated memory
    return 0;
}