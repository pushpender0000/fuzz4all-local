#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

#define MAX_ITER 10000
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

void complexCalculation(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    int32_t result = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        if (s.a > 0 && s.b[0] == 1) {
            result += s.a * 2 + s.b[1];
        } else {
            result -= s.a / 3 - s.b[2];
        }
    }
    printf("%d\n", result);
}

int main() {
    runTests(testFunction);
    complexCalculation(INITIAL_VALUE, (uint8_t[]){1, 2, 3, 4});
    return 0;
}