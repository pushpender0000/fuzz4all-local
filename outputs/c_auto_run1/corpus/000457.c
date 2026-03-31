#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

typedef void (*TestFunc)(MyStruct*);

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

void testFunction(MyStruct* s) {
    printStruct(s);
    printf("%u\n", hashStruct(s));
}

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

void runTests(TestFunc func, MyStruct* (*create)(int32_t, const uint8_t[])) {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    MyStruct* structs[sizeof(vals) / sizeof(vals[0])];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        structs[i] = create(vals[i], arr[i]);
    }
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(structs[i]);
    }
}

void complexFunction() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

void complexMacroTest() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        COMPLICATED_MACRO(vals[i], arr[i]);
    }
}

void runComplexTests() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

int main() {
    runTests(testFunction, createStruct);
    complexFunction();
    complexMacroTest();
    runComplexTests();
    return 0;
}