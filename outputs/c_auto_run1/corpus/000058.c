#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t a;
    uint16_t b;
    float c;
} ComplexStruct;

#define MAX_COMPLEX 50

ComplexStruct complexArray[MAX_COMPLEX];

void initComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
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
        totalHash += calculateHash(&complexArray[i]);
    }
    printf("%u\n", totalHash);
}

void (*printFuncPtr)(void) = printHash;

uint32_t multiplyAndAdd(int index, int multiplier) {
    ComplexStruct cs = complexArray[index];
    uint32_t result = (uint32_t)(cs.a * multiplier + cs.b * 2 + (uint16_t)(cs.c * 3.14));
    return result;
}

void printComplexStruct(int index) {
    ComplexStruct cs = complexArray[index];
    printf("a: %d, b: %hu, c: %f\n", cs.a, cs.b, cs.c);
}

int main() {
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        initComplex(i, rand(), (uint16_t)(rand() % 100), (float)(rand()) / RAND_MAX * 100);
    }
    printFuncPtr();
    return 0;
}