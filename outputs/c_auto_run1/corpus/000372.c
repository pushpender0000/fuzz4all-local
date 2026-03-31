#include <stdio.h>
#include <stdint.h>

typedef int32_t MyInt;
typedef uint8_t Byte;

typedef struct {
    MyInt a;
    Byte b[4];
} MyStruct;

MyStruct createStruct(MyInt val, const Byte arr[]) {
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

void testFunction(MyInt x, const Byte y[]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

typedef void (*TestFunc)(MyInt, const Byte[]);

void runTests(TestFunc func) {
    MyInt vals[] = {10, -10, INT32_MIN, INT32_MAX};
    Byte arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexFunction() {
    MyInt vals[] = {10, -10, INT32_MIN, INT32_MAX};
    Byte arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

void complexMacroTest() {
    MyInt vals[] = {10, -10, INT32_MIN, INT32_MAX};
    Byte arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        COMPLICATED_MACRO(vals[i], arr[i]);
    }
}

void runComplexTests() {
    MyInt vals[] = {10, -10, INT32_MIN, INT32_MAX};
    Byte arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

int main() {
    runTests(testFunction);
    complexFunction();
    complexMacroTest();
    runComplexTests();
    return 0;
}