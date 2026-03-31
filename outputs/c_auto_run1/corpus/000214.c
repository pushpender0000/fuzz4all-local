#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t data;
    uint8_t *ptr;
} MyStruct;

#define MAX_ITER 100
#define INITIAL_VALUE 50

MyStruct createStruct(int32_t val, uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    s.ptr = (uint8_t *)malloc(4 * sizeof(uint8_t));
    for (int i = 0; i < 4; ++i) {
        s.ptr[i] = arr[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->ptr[i];
    }
    free(s->ptr); // Ensure memory is freed to avoid leaks
    return h;
}

void testFunction(int32_t x, uint8_t y[]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFunc)(int32_t, uint8_t[]);

void runTests(TestFunc func) {
    int32_t vals[] = {INITIAL_VALUE, -INITIAL_VALUE};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[4] = {1, 2, 3, 4}; // Fixed array to avoid UB in function definition
        func(vals[i], arr);
    }
}

void complexOperation() {
    MyStruct arrayOfStructs[MAX_ITER];
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < MAX_ITER; ++i) {
        arrayOfStructs[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("%u\n", totalHash);
}

void nestedComplexOperation() {
    MyStruct nestedArray[MAX_ITER];
    uint8_t innerInitialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < MAX_ITER; ++i) {
        nestedArray[i] = createStruct(INITIAL_VALUE * i, innerInitialArray);
    }
    uint32_t nestedTotalHash = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        nestedTotalHash += hashStruct(&nestedArray[i]);
    }
    printf("%u\n", nestedTotalHash);
}

int main() {
    runTests(testFunction);
    complexOperation();
    nestedComplexOperation();
    return 0;
}