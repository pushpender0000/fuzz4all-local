#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val};
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

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

void complexFunction(int32_t a, uint8_t b[4], int32_t c) {
    MyStruct s1 = createStruct(a, b);
    printStruct(&s1);
    printf("%u\n", hashStruct(&s1));

    MyStruct s2 = createStruct(c, b);
    printStruct(&s2);
    printf("%u\n", hashStruct(&s2));
}

void nestedFunction(int32_t a, uint8_t b[4], int32_t c) {
    complexFunction(a, b, c);
    MyStruct s = createStruct(c, b);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    runTests(testFunction);
    
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        nestedFunction(vals[i], arr[i], vals[(i + 1) % 4]);
    }

    return 0;
}