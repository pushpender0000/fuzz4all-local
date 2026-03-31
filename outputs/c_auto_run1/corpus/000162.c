#include <stdio.h>
#include <stdint.h>

// Define a complex struct
typedef struct {
    int32_t data;
    uint8_t values[4];
} ComplexStruct;

#define ARRAY_SIZE 100
#define INITIAL_VALUE 5

// Function to create a ComplexStruct instance
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.values[i] = arr[i];
    }
    return s;
}

// Function to print the data of a ComplexStruct
void printComplexStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
}

// Function to hash the ComplexStruct (simple example, can be complexified more)
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->values[i];
    }
    return h;
}

// Function to demonstrate function pointer usage
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