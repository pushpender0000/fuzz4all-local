#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.a = val * 5; // Increased complexity by multiplying the value
    for (int i = 0; i < 4; ++i) {
        s.b[i] = arr[i] + 3; // Further increased complexity with addition and shift operations
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->a);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)(s->a >> 8); // Shift operation to increase complexity
    for (int i = 0; i < 4; ++i) {
        h += ((uint32_t)s->b[i] << 4) * 2; // Complex operations in the loop
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
    int32_t vals[] = {10, -10, 1000, -1000}; // Increased range for more diverse testing
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

int main() {
    runTests(testFunction);
    return 0;
}