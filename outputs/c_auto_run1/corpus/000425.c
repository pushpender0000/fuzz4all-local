#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t (*HashFunc)(const void*, size_t);

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val};
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

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    uint32_t h = hashStruct(&s); \
    printf("%u\n", h); \
})

void testFunction(int32_t x, const uint8_t arr[]) {
    MyStruct s = createStruct(x, arr);
    printStruct(&s);
    uint32_t h = hashStruct(&s);
    printf("%u\n", h);
}

void runTests(void (*func)(int32_t, const uint8_t[])) {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], (const uint8_t[]){0, 1, 2, 3});
    }
}

void runComplexTests() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], (const uint8_t[]){i, i+1, i+2, i+3});
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

int main() {
    runTests(testFunction);
    COMPLICATED_MACRO(10, (const uint8_t[]){1, 2, 3, 4});
    runComplexTests();
    return 0;
}