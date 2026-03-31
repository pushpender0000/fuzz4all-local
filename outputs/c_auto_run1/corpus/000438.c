#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define a complex type using typedef and struct
typedef struct {
    int32_t data;
    uint8_t buffer[4];
} ComplexStruct;

// Macro to calculate the size of the struct
#define SIZEOF_COMPLEXSTRUCT (sizeof(ComplexStruct))

// Inline function to initialize a ComplexStruct instance
static inline void initStruct(ComplexStruct *s, int32_t val, const uint8_t arr[4]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->buffer[i] = arr[i];
    }
}

// Inline function to print the value of a ComplexStruct instance
static inline void printStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the contents of a ComplexStruct instance
uint32_t hashStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->buffer[i];
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
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // Create an array of ComplexStruct instances for testing
    ComplexStruct structs[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initStruct(&structs[i], vals[i], arr[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially
    TestFunc funcs[] = {printStruct, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    // Additional stress test: create a large array of ComplexStruct instances and manipulate them
    const int numInstances = 1024;
    ComplexStruct *largeArray = (ComplexStruct *)malloc(numInstances * sizeof(ComplexStruct));
    if (!largeArray) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numInstances; ++i) {
        initStruct(&largeArray[i], vals[i % 4], arr[i % 4]);
    }

    // Use a function pointer to call the print and hash functions on each instance in the large array
    for (int i = 0; i < numInstances; ++i) {
        runTests(funcs[i % 2], &largeArray[i]);
    }

    free(largeArray);
    return 0;
}