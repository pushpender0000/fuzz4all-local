#include <stdio.h>
#include <stdint.h>

typedef int32_t (*MathFunc)(int32_t, int32_t);

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

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

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

int32_t add(int32_t a, int32_t b) {
    return a + b;
}

int32_t sub(int32_t a, int32_t b) {
    return a - b;
}

void complexFunction(int32_t x, uint8_t y[4], MathFunc func) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
    int32_t result = func(s.a, (int32_t)y[0]);
    printf("Result of %s: %d\n", #func, result);
}

void runTests() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        complexFunction(vals[i], arr[i], add);
        complexFunction(vals[i], arr[i], sub);
    }
}

void dynamicDispatchFunction(int32_t x, uint8_t y[4], MathFunc func) {
    if (func == add || func == sub) {
        complexFunction(x, y, func);
    } else {
        printf("Unknown function pointer.\n");
    }
}

int main() {
    runTests();
    
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        dynamicDispatchFunction(vals[i], arr[i], add);
        dynamicDispatchFunction(vals[i], arr[i], sub);
    }

    return 0;
}