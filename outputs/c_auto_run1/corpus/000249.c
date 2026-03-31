#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define INITIAL_VALUE 10
#define MAX_ITER 500

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.bytes[i] = arr[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

#define ARRAY_SIZE 10
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define COMPLEX_OPERATION 1

#if COMPLEX_OPERATION
void complexOperation() {
    int32_t vals[] = {-INITIAL_VALUE * MAX_ITER, INITIAL_VALUE * (MAX_ITER / 2), -INITIAL_VALUE * (MAX_ITER / 4)};
    uint8_t arr[][4] = {{1}, {2, 3, 4, 5}, {6, 7, 8, 9}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        testFunction(vals[i], arr[i]);
    }
}
#endif

int main() {
    initializeArray();
    runTests(testFunction);
#if COMPLEX_OPERATION
    complexOperation();
#endif
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}