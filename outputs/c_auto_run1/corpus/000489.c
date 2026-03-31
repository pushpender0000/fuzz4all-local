#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t arr[4];
} MyStruct;

typedef void (*TestFunc)(MyStruct);

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->arr[i];
    }
    return h;
}

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val};
    for (int i = 0; i < 4; ++i) {
        s.arr[i] = arr[i];
    }
    return s;
}

void testFunction(MyStruct s) {
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define COMPLICATED_MACRO(val, arr) ({ \
    MyStruct s = createStruct(val, arr); \
    testFunction(s); \
})

void runTests(TestFunc func, int32_t vals[], uint8_t arrs[][4]) {
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arrs[i]);
        func(s);
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
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    runTests(testFunction, vals, arr);
    complexFunction();
    complexMacroTest();
    runComplexTests();
    return 0;
}