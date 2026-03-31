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
    return (uint32_t)(cs->a + cs->b + (uint16_t)cs->c);
}

void printHashes() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 5 == 0 && i != 0) {
            printf("%u\n", totalHash);
            totalHash = 0;
        }
        totalHash += calculateHash(&complexArray[i]);
    }
}

void (*printFuncPtr)(void) = printHashes;

#define INIT_COMPLEX_ARRAY \
    do { \
        for (int i = 0; i < MAX_COMPLEX; ++i) { \
            initComplex(i, i * 10, (uint16_t)(i * 20), (float)(i * 3.14)); \
        } \
    } while (0);

uint32_t sumAllHashes() {
    uint32_t totalSum = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        totalSum += calculateHash(&complexArray[i]);
    }
    return totalSum;
}

void printSumOfHashes() {
    printf("%u\n", sumAllHashes());
}

int main() {
    INIT_COMPLEX_ARRAY
    if (MAX_COMPLEX > 0) {
        ComplexStruct *lastElement = &complexArray[MAX_COMPLEX - 1];
        uint32_t lastHash = calculateHash(lastElement);
        printf("%u\n", lastHash);
    }
    printFuncPtr();
    printSumOfHashes();
    return 0;
}