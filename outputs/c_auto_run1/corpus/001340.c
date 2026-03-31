#include <stdio.h>
#include <stdint.h>

// Define a struct type for complex numbers
typedef struct {
    int32_t real;
    int32_t imag;
} Complex;

// Macro to initialize an array of complexes
#define INITIALIZE_COMPLEXES(arr) do { \
    for (int i = 0; i < ARRAY_SIZE; ++i) { \
        arr[i] = (Complex){.real = i * 10, .imag = -(i * 5)}; \
    } \
} while (0)

// Macro to print a complex number
#define PRINT_COMPLEX(c) printf("%d + %di\n", c.real, c.imag)

// Function to compute the magnitude of a complex number
inline uint32_t complexMagnitude(const Complex *c) {
    return (uint32_t)(c->real * c->real + c->imag * c->imag);
}

// Array of complexes, initialized by macro
Complex complexArray[ARRAY_SIZE];

// Function to use a function pointer to print each complex number
void runTests(void (*func)(const Complex*)) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        func(&complexArray[i]);
    }
}

// Test function that prints a complex number
void testFunction(const Complex *c) {
    PRINT_COMPLEX(*c);
}

// Main function demonstrating the use of macros, structs, and function pointers
int main() {
    INITIALIZE_COMPLEXES(complexArray);

    // Use a function pointer to run tests
    void (*printFunc)(const Complex*) = &testFunction;
    runTests(printFunc);

    uint32_t totalMagnitude = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue; // Skip every third element
        totalMagnitude += complexMagnitude(&complexArray[i]);
    }
    printf("Total Magnitude: %u\n", totalMagnitude);

    return 0;
}