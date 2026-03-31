#include <stdio.h>
#include <stdint.h>

// Define a complex type using typedef
typedef struct {
    int32_t data;
    uint8_t values[4];
} ComplexStruct;

#define ARRAY_SIZE 100
#define INITIAL_VALUE 5

// Function to create a ComplexStruct instance with specific mutations
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s;
    s.data = val * 2; // Mutation: double the value
    for (int i = 0; i < 4; ++i) {
        s.values[i] = arr[i] + 1; // Mutation: increment each element in array by 1
    }
    return s;
}

// Function to print the data of a ComplexStruct with specific formatting
void printComplexStruct(const ComplexStruct *s) {
    printf("%08d\n", s->data); // Mutation: format specifier for better visibility
}

// Function to hash the ComplexStruct using XOR operation for added complexity
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h ^= s->values[i]; // Mutation: use XOR instead of addition for hashing
    }
    return h;
}

// Function to demonstrate function pointer usage with complex struct manipulation
void testFunction(ComplexStruct (*func)(int32_t, const uint8_t[])) {
    ComplexStruct arrayOfStructs[ARRAY_SIZE];
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = func(INITIAL_VALUE * i, initialArray); // Use function pointer and mutate values
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashComplexStruct(&arrayOfStructs[i]); // Mutation: accumulate hashes in a new way
    }
    printf("%u\n", totalHash); // Print the final combined hash
}

// Main function to run the test with a specific struct creation function
int main() {
    void (*testFunc)(void (*)()) = (void (*)(void (*)())) &testFunction;
    testFunc(&createComplexStruct); // Use function pointer and mutate function behavior
    return 0;
}