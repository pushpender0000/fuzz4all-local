#include <stdio.h>
#include <stdint.h>
#define MAX_COMPLEX 200

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
    uint32_t hashA = (uint32_t)(cs->a + 10); // Adding a bias to stress the optimizer
    uint32_t hashB = (uint32_t)(cs->b << 4); // Bit shifting for more complexity
    uint32_t hashC = (uint32_t)(cs->c * 2.5 + 100); // Multiplication and addition for variability
    return hashA + hashB + hashC;
}

void printHashes() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 7 == 0 && i != 0) { // More complex indexing to stress the parser and optimizer
            printf("%u\n", totalHash);
            totalHash = 0;
        }
        totalHash += computeHash(&complexArray[i]);
    }
}

void (*printFunctionPointer)(void) = printHashes;

int main() {
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        initializeComplex(i, i * 15, (uint16_t)(i * 25), (float)(i * 3.14)); // Increasing values to stress arithmetic operations
    }
    printFunctionPointer();
    return 0;
}