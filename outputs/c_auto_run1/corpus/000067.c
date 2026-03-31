#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_COMPLEX 100

typedef struct {
    int32_t a;
    uint16_t b;
    float c;
} ComplexStruct;

ComplexStruct complexArray[MAX_COMPLEX];

void initComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
    if (index >= MAX_COMPLEX) return; // Ensure no out-of-bounds write
    complexArray[index].a = aVal;
    complexArray[index].b = bVal;
    complexArray[index].c = cVal;
}

uint32_t calculateHash(ComplexStruct *cs) {
    return (uint32_t)(cs->a + cs->b + (uint16_t)cs->c);
}

void printHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 5 == 0 && i != 0) { // Print hash every 5 elements to ensure output is not too short
            printf("%u\n", totalHash);
            totalHash = 0; // Reset for next set of hashes
        }
        totalHash += calculateHash(&complexArray[i]);
    }
}

void (*printFuncPtr)(void) = printHash;

int main() {
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        initComplex(i, i * 10, (uint16_t)(i * 20), (float)(i * 3.14));
    }
    printFuncPtr(); // Call the function pointer to ensure it calls printHash
    return 0;
}