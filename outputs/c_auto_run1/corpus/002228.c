#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
    uint32_t h = 0;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s.bytes[i] * 2;
        } else {
            h += s.bytes[i] / 2;
        }
    }
    printf("%u\n", h);
}

void complexOperation(int32_t a, int32_t b) {
    int32_t result = (a > b ? a : b) + ((a < b ? a : b) * 2);
    printf("%d\n", result);
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    runTests(testFunction);
    int32_t a = 50, b = -50;
    complexOperation(a, b);
    return 0;
}