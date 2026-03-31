#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint16_t b;
    float c;
} ComplexStruct;

#define MAX_COMPLEX 50

ComplexStruct complexArray[MAX_COMPLEX];

void initComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
    if (index >= MAX_COMPLEX) return;
    complexArray[index].a = aVal;
    complexArray[index].b = bVal;
    complexArray[index].c = cVal;
}

uint32_t calculateHash(ComplexStruct *cs) {
    uint32_t hashA = (uint32_t)(cs->a + 1); // Adding 1 to avoid zero hash for default struct initialization
    uint32_t hashB = (uint32_t)cs->b;
    uint32_t hashC = (uint32_t)cs->c;
    return hashA * hashB + (uint32_t)hashC; // Combining hashes with multiplication and addition
}

void printHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 5 == 0 && i != 0) {
            printf("%u\n", totalHash);
            totalHash = 0;
        }
        totalHash += calculateHash(&complexArray[i]);
    }
}

void (*printFuncPtr)(void) = printHash;

int main() {
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        initComplex(i, i * 10, (uint16_t)(i % 256), (float)(i * 3.14)); // Fixed initialization values for deterministic output
    }
    printFuncPtr();
    return 0;
}