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

void initializeComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
    if (index >= MAX_COMPLEX) return;
    complexArray[index].a = aVal;
    complexArray[index].b = bVal;
    complexArray[index].c = cVal;
}

uint32_t computeHash(ComplexStruct *cs) {
    uint32_t hash1 = (uint32_t)(cs->a + cs->b);
    uint32_t hash2 = (uint32_t)(hash1 + (uint16_t)cs->c);
    return hash2;
}

void printHashes() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 5 == 0 && i != 0) {
            printf("%u\n", totalHash);
            totalHash = 0;
        }
        totalHash += computeHash(&complexArray[i]);
    }
}

void (*printFunctionPointer)(void) = printHashes;

int main() {
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        initializeComplex(i, i * 10, (uint16_t)(i * 20), (float)(i * 3.14));
    }
    printFunctionPointer();
    return 0;
}