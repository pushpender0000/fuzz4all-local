#include <stdio.h>
#include <stdint.h>

typedef int32_t MyInt;

typedef struct {
    MyInt data;
    uint8_t bytes[4];
} MyStruct;

#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

#define HASH(s) ((uint32_t)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

typedef void (*TestFunc)(MyInt, uint8_t[4]);

void initializeStruct(MyStruct *s, MyInt val, uint8_t arr[4]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

void testFunction(MyInt x, uint8_t y[4]) {
    MyStruct s;
    initializeStruct(&s, x, y);
    printf("%u\n", HASH(&s));
}

void runTests(TestFunc func) {
    MyInt vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexFunction(MyInt offset, uint8_t newBytes[4]) {
    MyStruct arrayOfStructs[50];
    for (int i = 0; i < 50; ++i) {
        if (i != offset && i % 7 == 0) { // Avoid specific indices to avoid undefined behavior
            initializeStruct(&arrayOfStructs[i], 10 * i, newBytes);
        } else {
            arrayOfStructs[i] = CREATESTRUCT(10 * i, newBytes);
        }
    }
    printf("Complex Function Hash: %u\n", HASH(&arrayOfStructs[offset]));
}

typedef void (*TestFuncPtr)(MyInt, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    MyInt vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

int main() {
    runTests(testFunction);
    complexFunction(5, (uint8_t[]){17, 18, 19, 20});
    runTestsWithPointer(testFunction);
    return 0;
}