#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t val;
    uint8_t data[4];
} MyStruct;

MyStruct createStruct(int32_t v, const uint8_t d[4]) {
    MyStruct s = {v};
    for (int i = 0; i < 4; ++i) {
        s.data[i] = d[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->val;
    for (int i = 0; i < 4; ++i) {
        h += s->data[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%u\n", hashStruct(s));
}

typedef void (*TestFunc)(MyStruct*);

void testFunction(MyStruct *s) {
    printStruct(s);
}

#define COMPLICATED_MACRO(s) ({ \
    MyStruct temp = createStruct((s)->val, (s)->data); \
    printStruct(&temp); \
})

void runTests(TestFunc func, MyStruct *s) {
    func(s);
}

int main() {
    int32_t vals[] = {10, -10, INT32_MIN, INT32_MAX};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        runTests(testFunction, &s);
        COMPLICATED_MACRO(&s);
    }
    
    return 0;
}