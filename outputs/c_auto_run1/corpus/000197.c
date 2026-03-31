#include <stdio.h>
#include <stdint.h>

// Define complex types
typedef struct {
    int32_t data;
    uint8_t values[4];
} ComplexStruct;

typedef struct {
    double a;
    float b;
} AnotherComplexType;

#define ARRAY_SIZE 100
#define INITIAL_VALUE 5

// Function to create a ComplexStruct instance with specific data and array values
ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.values[i] = arr[i];
    }
    return s;
}

// Function to hash the ComplexStruct using a more complex algorithm
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->values[i] * (i + 1);
    }
    return h;
}

// Function to initialize an array of AnotherComplexType with specific values
void initAnotherComplexArray(AnotherComplexType arr[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i].a = (double)(INITIAL_VALUE * i);
        arr[i].b = (float)(INITIAL_VALUE * i + 1);
    }
}

// Function to calculate the sum of hashes of AnotherComplexType array elements
uint32_t sumOfHashes(const AnotherComplexType arr[]) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ComplexStruct temp = createComplexStruct((int32_t)(arr[i].a), (uint8_t *)(&arr[i].b));
        totalHash += hashComplexStruct(&temp);
    }
    return totalHash;
}

// Main function to demonstrate function pointer usage and complex type handling
int main() {
    AnotherComplexType arrayOfComplexTypes[ARRAY_SIZE];
    initAnotherComplexArray(arrayOfComplexTypes);
    uint32_t result = sumOfHashes(arrayOfComplexTypes);
    printf("%u\n", result);
    return 0;
}