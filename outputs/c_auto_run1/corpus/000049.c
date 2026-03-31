#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define a complex struct with nested fields
typedef struct {
    int32_t data;
    uint8_t *ptr;
} ComplexStruct;

// Macro to calculate the size of the struct
#define SIZEOF_COMPLEXSTRUCT (sizeof(ComplexStruct) + 5)

// Inline function to initialize a ComplexStruct instance
static inline void initStruct(ComplexStruct *s, int32_t val, uint8_t arr[4]) {
    s->data = val;
    s->ptr = (uint8_t*)malloc(4);
    for (int i = 0; i < 4; ++i) {
        s->ptr[i] = arr[i];
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
        h += s->ptr[i];
    }
    free(s->ptr); // Free the allocated memory before returning the hash
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

    return 0;
}