#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t buffer[4];
} ComplexStruct;

#define MAX_ITER 1000
#define INITIAL_VALUE 10

ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    ComplexStruct s;
    s.data = (val > 0) ? (val + 1) : (val - 1); // Introduce complexity with conditional arithmetic
    for (int i = 0; i < sizeof(s.buffer); ++i) {
        s.buffer[i] = arr[i];
    }
    return s;
}

uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < sizeof(s->buffer); ++i) {
        h += s->buffer[i] * (i + 17); // Complex multiplication with a non-standard multiplier
    }
    return h;
}

void printComplexStruct(const ComplexStruct *s) {
    printf("%d\n", s->data); // Print the value using standard output
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
    ComplexStruct s = createComplexStruct(x, y);
    printComplexStruct(&s);
    printf("%u\n", hashComplexStruct(&s));
}

int main() {
    runTests(testFunction);
    return 0;
}