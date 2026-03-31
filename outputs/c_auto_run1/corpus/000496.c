#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int32_t data;
    uint8_t buffer[4];
} MyStruct;

typedef void (*TestFunc)(MyStruct*);

void initializeStruct(MyStruct *s, int32_t val, const uint8_t arr[]) {
    s->data = val;
    memcpy(s->buffer, arr, 4);
}

uint32_t hashStruct(const MyStruct *s) {
    return (uint32_t)s->data + *(uint32_t*)s->buffer;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void complexFunctionality(MyStruct *s, uint8_t val) {
    s->data += (int32_t)val;
    for (int i = 0; i < 4; ++i) {
        s->buffer[i] ^= val;
    }
}

void testFunction(MyStruct *s, uint8_t val) {
    initializeStruct(s, (int32_t)val, &val);
    printStruct(s);
    printf("%u\n", hashStruct(s));
    complexFunctionality(s, val);
    printStruct(s);
    printf("%u\n", hashStruct(s));
}

#define COMPLICATED_MACRO(s, val) ({ \
    initializeStruct(s, (int32_t)val, &val); \
    printStruct(s); \
    printf("%u\n", hashStruct(s)); \
    complexFunctionality(s, val); \
    printStruct(s); \
    printf("%u\n", hashStruct(s)); \
})

void runTests(TestFunc func) {
    MyStruct s;
    uint8_t vals[] = {10, 20, 30, 40};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(&s);
    }
}

void complexFunction() {
    MyStruct s;
    uint8_t vals[] = {10, 20, 30, 40};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initializeStruct(&s, (int32_t)vals[i], &vals[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
        complexFunctionality(&s, vals[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

void complexMacroTest() {
    MyStruct s;
    uint8_t vals[] = {10, 20, 30, 40};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        COMPLICATED_MACRO(&s, vals[i]);
    }
}

void runComplexTests() {
    MyStruct s;
    uint8_t vals[] = {10, 20, 30, 40};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initializeStruct(&s, (int32_t)vals[i], &vals[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
        complexFunctionality(&s, vals[i]);
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