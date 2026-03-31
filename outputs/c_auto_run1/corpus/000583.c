#include <stdio.h>
#include <stdint.h>

// Define a complex union for fuzzing
typedef union {
    int32_t data;
    uint8_t buffer[4];
} ComplexUnion;

// Macro to calculate the size of the union
#define SIZEOF_COMPLEXUNION (sizeof(ComplexUnion))

// Inline function to initialize a ComplexUnion instance
static inline void initUnion(ComplexUnion *u, int32_t val, const uint8_t arr[4]) {
    u->data = val;
    for (int i = 0; i < 4; ++i) {
        u->buffer[i] = arr[i];
    }
}

// Inline function to print the value of a ComplexUnion instance
static inline void printUnion(const ComplexUnion *u) {
    printf("%d\n", u->data);
}

// Function to hash the contents of a ComplexUnion instance
uint32_t hashUnion(const ComplexUnion *u) {
    uint32_t h = (uint32_t)u->data;
    for (int i = 0; i < 4; ++i) {
        h += u->buffer[i];
    }
    return h;
}

// Function pointer type
typedef void (*TestFuncUnion)(const ComplexUnion *);

// Function that uses a function pointer to operate on a union instance
void runTestsUnion(TestFuncUnion func, const ComplexUnion *u) {
    func(u);
}

// Main function to create and test multiple instances of ComplexUnion
int main() {
    // Define arrays for initialization
    int32_t vals[] = {10, -10, 1000, -1000};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // Create an array of ComplexUnion instances for testing
    ComplexUnion unions[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initUnion(&unions[i], vals[i], arr[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially
    TestFuncUnion funcUnions[] = {printUnion, (TestFuncUnion)hashUnion};
    for (int i = 0; i < sizeof(funcUnions) / sizeof(funcUnions[0]); ++i) {
        runTestsUnion(funcUnions[i], &unions[i % 4]);
    }

    return 0;
}