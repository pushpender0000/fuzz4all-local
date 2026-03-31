#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t val;
    uint8_t data[4];
} MyStruct;

MyStruct createStruct(int32_t v, const uint8_t arr[]) {
    MyStruct s;
    s.val = v;
    for (int i = 0; i < 4; ++i) {
        s.data[i] = arr[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->val;
    for (int i = 0; i < 4; ++i) {
        h += s->data[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->val);
}

typedef void (*TestFunc)(int32_t, const uint8_t[]);

void testFunction(int32_t x, const uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define MAX_ITER 1000
#define INITIAL_VALUE 10

void runTests(TestFunc func) {
    int32_t vals[] = {INITIAL_VALUE, -INITIAL_VALUE};
    const uint8_t arr[][4] = {{0}, {1, 2, 3, 4}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void nestedComplexCalculation() {
    int32_t vals[] = {1, -1};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        for (int j = 0; j < sizeof(vals) / sizeof(vals[0]); ++j) {
            int32_t x = vals[i] * vals[j];
            const uint8_t y[4] = {0}; // Example array initialization
            testFunction(x, y);
        }
    }
}

int main() {
    runTests(testFunction);
    nestedComplexCalculation();
    return 0;
}