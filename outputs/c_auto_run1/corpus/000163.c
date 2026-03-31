#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
    double c;
} ComplexStruct;

#define INITIAL_VALUE 10
#define MAX_ITER 500

ComplexStruct createComplexStruct(int32_t val, const uint8_t arr[], double d) {
    ComplexStruct s;
    s.a = val;
    for (int i = 0; i < 4; ++i) {
        s.b[i] = arr[i];
    }
    s.c = d;
    return s;
}

void printComplexStruct(const ComplexStruct *s) {
    printf("%d %f\n", s->a, s->c);
}

uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->a;
    for (int i = 0; i < 4; ++i) {
        h += s->b[i];
    }
    return h + *(uint32_t *)&(s->c); // Ensure double is hashed correctly, though this might be undefined behavior.
}

#define COMPLEX_OPERATION(n) ({ \
    ComplexStruct arrayOfComplexStructs[MAX_ITER]; \
    uint8_t initialArray[] = {1, 2, 3, 4}; \
    double initialDoubleValue = 3.14; \
    for (int i = 0; i < MAX_ITER; ++i) { \
        arrayOfComplexStructs[i] = createComplexStruct(INITIAL_VALUE * i, initialArray, initialDoubleValue + i); \
    } \
    uint32_t totalHash = 0; \
    for (int i = 0; i < MAX_ITER; ++i) { \
        totalHash += hashComplexStruct(&arrayOfComplexStructs[i]); \
    } \
    printComplexStruct(&arrayOfComplexStructs[(n % MAX_ITER)]); \
    printf("%u\n", totalHash + (n * 100)); \
})

void runTests() {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        ComplexStruct s = createComplexStruct(vals[i], arr[i], 0.0);
        printComplexStruct(&s);
        printf("%u\n", hashComplexStruct(&s));
    }
}

int main() {
    runTests();
    COMPLEX_OPERATION(4294967295); // A large number to stress the loop and struct handling.
    return 0;
}