#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

#define MAX_ITER 1000
#define INITIAL_VALUE 10

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.a = val;
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

#define ARRAY_SIZE 100
uint32_t calculateHash(const uint8_t arr[], size_t size) {
    uint32_t h = 0;
    for (size_t i = 0; i < size; ++i) {
        h += arr[i];
    }
    return h;
}

void stressFunction(uint8_t data[]) {
    uint8_t array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = data[i % MAX_ITER];
    }
    printf("%u\n", calculateHash(array, ARRAY_SIZE));
}

int main() {
    uint8_t testData[MAX_ITER];
    for (int i = 0; i < MAX_ITER; ++i) {
        testData[i] = (uint8_t)(i * INITIAL_VALUE);
    }
    stressFunction(testData);
    runTests(testFunction);
    complexFunction();
    return 0;
}