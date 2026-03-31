#include <stdio.h>

typedef unsigned int uint;

typedef struct {
    int data;
    double precision;
} ComplexStruct;

#define MAX_COMPLEX 100

ComplexStruct complexArray[MAX_COMPLEX];

void initializeComplexArray() {
    for (uint i = 0; i < MAX_COMPLEX; ++i) {
        complexArray[i].data = (int)(i * 1.5);
        complexArray[i].precision = i * 0.1;
    }
}

uint calculateComplexHash(const ComplexStruct *cs) {
    return (uint)(cs->data + cs->precision);
}

void printComplexHash() {
    uint sum = 0;
    for (uint i = 0; i < MAX_COMPLEX; ++i) {
        sum += calculateComplexHash(&complexArray[i]);
    }
    printf("%u\n", sum);
}

typedef void (*FuncPtr)(void);

void funcOne() {
    printf("Function One Executed.\n");
}

void funcTwo() {
    printf("Function Two Executed.\n");
}

int main() {
    initializeComplexArray();
    FuncPtr funcPointers[2] = {funcOne, funcTwo};
    for (uint i = 0; i < 2; ++i) {
        funcPointers[i]();
    }
    printComplexHash();
    return 0;
}