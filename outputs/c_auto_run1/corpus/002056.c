#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

MyStruct createStruct(int32_t data, uint8_t bytes[4]) {
    return (MyStruct){data, {bytes[0], bytes[1], bytes[2], bytes[3]}};
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 != 0 && i % 13 != 0) { // Avoid specific indices to avoid undefined behavior
            arrayOfStructs[i] = createStruct(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
        }
    }
}

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    initializeArray();
    runTests(testFunction);
    return 0;
}