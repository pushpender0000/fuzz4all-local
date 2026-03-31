#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t buffer[4];
} MyStruct;

#define MAX_ITER 1000
#define INITIAL_VALUE 10

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.buffer[i] = arr[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->buffer[i];
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
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexFunction() {
    MyStruct s[MAX_ITER];
    uint8_t arr[MAX_ITER][4];
    for (int i = 0; i < MAX_ITER; ++i) {
        s[i] = createStruct(i * INITIAL_VALUE, &arr[i]);
    }
    for (int i = 0; i < MAX_ITER; ++i) {
        printStruct(&s[i]);
        printf("%u\n", hashStruct(&s[i]));
    }
}

void nestedFunction() {
    MyStruct nestedStructs[MAX_ITER];
    for (int i = 0; i < MAX_ITER; ++i) {
        nestedStructs[i] = createStruct(i * INITIAL_VALUE, &arr[i]);
    }
}

#define ARRAY_SIZE 100
uint8_t largeArray[ARRAY_SIZE];

void largeArrayFunction() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        largeArray[i] = (uint8_t)(i % 256);
    }
    MyStruct s = createStruct(INITIAL_VALUE, largeArray);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    runTests(testFunction);
    complexFunction();
    nestedFunction();
    largeArrayFunction();
    return 0;
}