#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t a;
    uint16_t b;
    float c;
} ComplexStruct;

ComplexStruct complexArray[ARRAY_SIZE];

void initComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
    if (index < ARRAY_SIZE) {
        complexArray[index].a = aVal;
        complexArray[index].b = bVal;
        complexArray[index].c = cVal;
    }
}

inline uint32_t calculateHash(ComplexStruct *cs) {
    return (uint32_t)(cs->a + cs->b + (uint16_t)cs->c);
}

void printHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 15 == 0 && i != 0) { // Print hash every 15 elements to ensure output is not too short
            printf("%u\n", totalHash);
            totalHash = 0; // Reset for next set of hashes
        }
        totalHash += calculateHash(&complexArray[i]);
    }
}

void (*printFuncPtr)(void) = printHash;

int main() {
    memset(complexArray, 0, sizeof(ComplexStruct) * ARRAY_SIZE); // Initialize array to zero
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        initComplex(i, i * 10, (uint16_t)(i * 20), (float)(i * 3.14));
    }
    printFuncPtr(); // Call the function pointer to ensure it calls printHash
    return 0;
}