#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

#define MAX_ITER 1000
#define INITIAL_VALUE 10

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.a = val;
    for (int i = 0; i < 4; ++i) {
        s.b[i] = arr[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->a);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->a;
    for (int i = 0; i < 4; ++i) {
        h += s->b[i];
    }
    return h;
}

#define ARRAY_SIZE 10

void generateArray(uint8_t arr[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (uint8_t)(INITIAL_VALUE * i);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
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

void largeLoop() {
    uint8_t arr[ARRAY_SIZE];
    generateArray(arr);
    MyStruct structs[MAX_ITER];
    for (int i = 0; i < MAX_ITER; ++i) {
        structs[i] = createStruct(INITIAL_VALUE * i, &arr[i % ARRAY_SIZE]);
    }
    uint32_t largeLoopHash = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        largeLoopHash += hashStruct(&structs[i]);
    }
    printf("%u\n", largeLoopHash);
}

int main() {
    runTests(testFunction);
    complexOperation();
    nestedComplexOperation();
    largeLoop();
    return 0;
}