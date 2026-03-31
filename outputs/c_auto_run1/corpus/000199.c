#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t value;
    uint8_t data[4];
} ComplexStruct;

typedef void (*FuncPtr)(ComplexStruct*);

void initializeStruct(ComplexStruct *cs, int32_t val, const uint8_t arr[]) {
    cs->value = val;
    for (int i = 0; i < 4; ++i) {
        cs->data[i] = arr[i];
    }
}

void printStruct(const ComplexStruct *cs) {
    printf("%d\n", cs->value);
}

uint32_t hashStruct(const ComplexStruct *cs) {
    uint32_t h = (uint32_t)cs->value;
    for (int i = 0; i < 4; ++i) {
        h += cs->data[i];
    }
    return h;
}

void complexFunction(ComplexStruct *s1, ComplexStruct *s2) {
    printStruct(s1);
    printf("%u\n", hashStruct(s1));
    printStruct(s2);
    printf("%u\n", hashStruct(s2));
}

void runTests(FuncPtr func, ComplexStruct s1, ComplexStruct s2) {
    func(&s1);
    func(&s2);
}

#define COMPLICATED_MACRO(x, y) ({ \
    ComplexStruct s = {.value = x}; \
    for (int i = 0; i < 4; ++i) { \
        s.data[i] = y[i]; \
    } \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

void polymorphicFunction(ComplexStruct *s, FuncPtr func) {
    func(s);
}

int main() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    
    ComplexStruct s1, s2;
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initializeStruct(&s1, vals[i], arr[i]);
        initializeStruct(&s2, vals[(i + 1) % 4], arr[(i + 1) % 4]);
        complexFunction(&s1, &s2);
    }
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initializeStruct(&s1, vals[i], arr[i]);
        runTests(printStruct, s1, s2);
    }
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initializeStruct(&s1, vals[i], arr[i]);
        polymorphicFunction(&s1, printStruct);
    }

    return 0;
}