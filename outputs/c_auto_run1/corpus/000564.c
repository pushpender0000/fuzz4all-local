#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 30

typedef struct {
    int16_t data;
    uint8_t bytes[2];
} SmallStruct;

typedef struct {
    double real;
    double imag;
} ComplexNumber;

void initializeSmallStructs(SmallStruct *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i].data = (int16_t)(i * 5);
        arr[i].bytes[0] = (uint8_t)(i % 256);
        arr[i].bytes[1] = (uint8_t)((i + 1) % 256);
    }
}

void printSmallStruct(const SmallStruct *s) {
    printf("%d\n", s->data);
}

ComplexNumber multiplyComplex(const ComplexNumber *a, const ComplexNumber *b) {
    ComplexNumber result;
    result.real = a->real * b->real - a->imag * b->imag;
    result.imag = a->real * b->imag + a->imag * b->real;
    return result;
}

void printComplex(const ComplexNumber *c) {
    printf("%f + %fi\n", c->real, c->imag);
}

typedef void (*ComplexFunc)(const ComplexNumber *);

void runTests(ComplexFunc func, const ComplexNumber *arr, size_t arrSize) {
    for (size_t i = 0; i < arrSize; ++i) {
        func(&arr[i]);
    }
}

void testFunction(const ComplexNumber *a, const ComplexNumber *b) {
    ComplexNumber result = multiplyComplex(a, b);
    printComplex(&result);
}

SmallStruct arrayOfSmallStructs[ARRAY_SIZE];

void initializeArray() {
    initializeSmallStructs(arrayOfSmallStructs, ARRAY_SIZE);
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printSmallStruct(&arrayOfSmallStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += arrayOfSmallStructs[i].data;
    }
    return totalHash;
}

void complexFunction(size_t index, const ComplexNumber *newVal) {
    if (index >= 0 && index < ARRAY_SIZE) {
        arrayOfSmallStructs[index] = (SmallStruct){.data = newVal->real, .bytes = {newVal->imag, 0}};
    } else {
        printf("Index out of bounds\n");
    }
}

void stressTest() {
    initializeArray();
    ComplexNumber complexArray[ARRAY_SIZE / 2];
    for (size_t i = 0; i < ARRAY_SIZE / 2; ++i) {
        complexArray[i] = (ComplexNumber){.real = i * 1.1, .imag = i * 1.2};
    }

    runTests(testFunction, complexArray, ARRAY_SIZE / 2);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    ComplexNumber newVal = {.real = -100.0, .imag = 150.0};
    complexFunction(ARRAY_SIZE / 2 + ARRAY_SIZE / 4, &newVal);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);
}

int main() {
    stressTest();
    return 0;
}