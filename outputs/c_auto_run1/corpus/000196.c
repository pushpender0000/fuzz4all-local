#include <stdio.h>
#include <stdint.h>

// Define complex types
typedef struct {
    int32_t data;
    uint8_t values[4];
} ComplexStruct;

typedef struct {
    double x, y;
} Point;

#define ARRAY_SIZE 100
#define INITIAL_VALUE 5

// Function to create a complex struct with specific operations
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s;
    s.data = val * 2; // Increased complexity by adding an operation
    for (int i = 0; i < 4; ++i) {
        s.values[i] = arr[i];
    }
    return s;
}

// Function to hash the ComplexStruct using a more complex algorithm
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)(s->data + 0.5); // Adding a floating point operation for complexity and diversity
    for (int i = 0; i < 4; ++i) {
        h += s->values[i] * ((i+1)*37); // More operations to increase complexity
    }
    return h;
}

// Function pointer demonstration using a function that creates a complex struct
void testFunction(ComplexStruct (*func)(int32_t, const uint8_t[])) {
    ComplexStruct arrayOfStructs[ARRAY_SIZE];
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = func(INITIAL_VALUE * i, initialArray);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashComplexStruct(&arrayOfStructs[i]);
    }
    printf("%u\n", totalHash);
}

// Main function to run the test with a specific struct creation function
int main() {
    // Use inline function for demonstration (can be replaced by lambda if supported)
    void (*testFunc)(void (*)()) = (void (*)(void (*)())) &testFunction;
    testFunc(&createComplexStruct);
    return 0;
}