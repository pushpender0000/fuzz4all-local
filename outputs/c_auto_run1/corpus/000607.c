#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define INITIAL_VALUE 10
#define MAX_ITER 500

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printf("%u\n", hashStruct(&s));
}

uint32_t complexCalculation() {
    uint32_t sum = 0;
    for (int i = 1; i <= MAX_ITER; ++i) {
        for (int j = 0; j < 4; ++j) {
            MyStruct s = createStruct(INITIAL_VALUE * i, (uint8_t[]){j, j+1, j+2, j+3});
            sum += hashStruct(&s);
        }
    }
    return sum;
}

int main() {
    uint32_t totalHash = complexCalculation();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}