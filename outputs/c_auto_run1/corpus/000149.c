#include <stdio.h>

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned long uint32;
typedef signed long int32;

typedef struct {
    uint32 a;
    int8 b[4];
} MyStruct;

#define ARRAY_SIZE 10

MyStruct createStruct(uint32 val, const int8 arr[]) {
    MyStruct s;
    s.a = val;
    for (int i = 0; i < 4; ++i) {
        s.b[i] = arr[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%u\n", s->a);
}

uint32 hashStruct(const MyStruct *s) {
    uint32 h = s->a;
    for (int i = 0; i < 4; ++i) {
        h += s->b[i];
    }
    return h;
}

typedef void (*TestFunc)(MyStruct *);

void runTests(TestFunc func, MyStruct *arrayOfStructs) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct((uint32)(i * 10), (const int8 *)&i);
    }
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        func(&arrayOfStructs[i]);
    }
}

void testFunction(MyStruct *s) {
    printStruct(s);
    printf("%u\n", hashStruct(s));
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    runTests(testFunction, arrayOfStructs);
    return 0;
}