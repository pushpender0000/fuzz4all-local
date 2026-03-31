#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double real;
    double imag;
} ComplexNumber;

MyStruct arrayOfStructs[20];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 20; ++i) {
        if (i != 5) {
            arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {initialArray[0], initialArray[1], initialArray[2], initialArray[3]}};
        }
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

#define ARRAY_SIZE 20

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

ComplexNumber complexMath(double a, double b) {
    ComplexNumber c = {a + b, 0}; // Ignoring imaginary part for simplicity
    return c;
}

void testComplexMath() {
    ComplexNumber result = complexMath(3.14, 2.71);
    printf("%.2f\n", result.real);
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break;
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    testComplexMath();

    return 0;
}