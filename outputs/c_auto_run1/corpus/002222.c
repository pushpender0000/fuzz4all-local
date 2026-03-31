#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double precisionData;
    int64_t largeInt;
} ComplexStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];
ComplexStruct complexArray[ARRAY_SIZE / 2];

void initializeArrays() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = (MyStruct){10 * i, {i, i + 1, i + 2, i + 3}};
    }
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        complexArray[i] = (ComplexStruct){(double)(i * 1.5), (int64_t)(i * 1000)};
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

uint32_t hashComplex(const ComplexStruct *c) {
    uint32_t h = (uint32_t)(c->precisionData * 100);
    h += c->largeInt % 256;
    return h;
}

void printStructs() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("%d\n", arrayOfStructs[i].data);
        } else {
            printf("%u\n", hashStruct(&arrayOfStructs[i]));
        }
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        if (i % 7 == 0 && i % 11 == 0) {
            printf("%ld\n", complexArray[i].largeInt);
        } else {
            printf("%u\n", hashComplex(&complexArray[i]));
        }
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
    printf("%u\n", hashStruct(&s));
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    initializeArrays();
    printStructs();
    printComplexArray();
    runTests(testFunction);
    return 0;
}