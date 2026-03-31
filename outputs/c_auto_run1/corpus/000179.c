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

void complexCalculation() {
    int32_t vals[] = {1, -1, INITIAL_VALUE, -INITIAL_VALUE};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        for (int j = 0; j < sizeof(vals) / sizeof(vals[0]); ++j) {
            int32_t x = vals[i] * vals[j];
            uint8_t y[4] = {0}; // Example array initialization
            testFunction(x, y);
        }
    }
}

void nestedComplexCalculation() {
    int32_t vals[] = {1, -1, INITIAL_VALUE, -INITIAL_VALUE};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        for (int j = 0; j < sizeof(vals) / sizeof(vals[0]); ++j) {
            for (int k = 0; k < sizeof(vals) / sizeof(vals[0]); ++k) {
                int32_t x = vals[i] * vals[j] + vals[k];
                uint8_t y[4] = {0}; // Example array initialization
                testFunction(x, y);
            }
        }
    }
}

void stressTest() {
    int32_t vals[] = {1, -1, INITIAL_VALUE, -INITIAL_VALUE};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        for (int j = 0; j < sizeof(vals) / sizeof(vals[0]); ++j) {
            for (int k = 0; k < sizeof(vals) / sizeof(vals[0]); ++k) {
                for (int l = 0; l < sizeof(vals) / sizeof(vals[0]); ++l) {
                    int32_t x = vals[i] * vals[j] + vals[k] - vals[l];
                    uint8_t y[4] = {0}; // Example array initialization
                    testFunction(x, y);
                }
            }
        }
    }
}

int main() {
    runTests(testFunction);
    complexCalculation();
    nestedComplexCalculation();
    stressTest();
    return 0;
}