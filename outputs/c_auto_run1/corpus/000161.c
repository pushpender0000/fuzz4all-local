#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define a complex struct with nested types
typedef struct {
    int32_t data;
    uint8_t *ptr;
} ComplexStruct;

#define SIZEOF_COMPLEXSTRUCT (sizeof(ComplexStruct) + 10)

// Macro to initialize a ComplexStruct instance
#define INIT_COMPLEXSTRUCT(inst, val) ((inst).data = (val), (inst).ptr = malloc(10))

// Inline function to calculate the size of the struct at runtime
static inline size_t calcSizeOfComplexStruct() {
    return SIZEOF_COMPLEXSTRUCT;
}

// Function to initialize a ComplexStruct instance with dynamic memory allocation
void initComplexStruct(ComplexStruct *s, int32_t val) {
    s->data = val;
    s->ptr = malloc(10); // Allocate 10 bytes for the pointer
}

// Function to print the value of a ComplexStruct instance
void printComplexStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the contents of a ComplexStruct instance
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (size_t i = 0; i < 10; ++i) {
        h += s->ptr[i];
    }
    return h;
}

// Function pointer type
typedef void (*TestFunc)(const ComplexStruct *);

// Function that uses a function pointer to operate on a struct instance
void runTests(TestFunc func, const ComplexStruct *s) {
    func(s);
}

// Main function to create and test multiple instances of ComplexStruct
int main() {
    // Define arrays for initialization
    int32_t vals[] = {10, -10, 1000, -1000};

    // Create an array of ComplexStruct instances for testing
    ComplexStruct structs[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initComplexStruct(&structs[i], vals[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially
    TestFunc funcs[] = {printComplexStruct, (TestFunc)hashComplexStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    // Free allocated memory
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        free(structs[i].ptr);
    }

    return 0;
}