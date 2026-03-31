#include <stdio.h>
#include <stdint.h>

#define MAX_ITER 500
#define INITIAL_VALUE 10

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.a = val * (val % 2 == 0 ? 1 : -1); // Ensure different signs for interesting cases
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

void complexFunction() {
    MyStruct s[MAX_ITER];
    uint8_t arr[MAX_ITER][4];
    for (int i = 0; i < MAX_ITER; ++i) {
        s[i] = createStruct(i * INITIAL_VALUE, &arr[i]);
    }
    for (int i = 0; i < MAX_ITER; ++i) {
        printStruct(&s[i]);
        printf("%u\n", hashStruct(&s[i]));
    }
}

void inline addOne(int32_t *val) {
    (*val)++;
}

void stressFunction() {
    int32_t val = INITIAL_VALUE;
    for (int i = 0; i < MAX_ITER; ++i) {
        addOne(&val);
        uint8_t arr[4] = {i, i+1, i+2, i+3};
        MyStruct s = createStruct(val, arr);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

int main() {
    runTests(testFunction);
    complexFunction();
    stressFunction();
    return 0;
}