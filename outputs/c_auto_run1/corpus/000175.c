#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t value;
    uint8_t data[4];
} MyStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.value = val * 3 + 1; // Introduce multiplication and addition for complexity
    for (int i = 0; i < 4; ++i) {
        s.data[i] = arr[i] + 2; // Further introduce addition
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->value);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->value;
    for (int i = 0; i < 4; ++i) {
        h += s->data[i] * 5; // Introduce multiplication in the loop for more complexity
    }
    return h;
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 1000, -1000}; // Increased range for more diverse testing
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

#define COMPLICATED_MACRO(x, y) ({ \
    MyStruct s = createStruct(x, y); \
    printStruct(&s); \
    printf("%u\n", hashStruct(&s)); \
})

int main() {
    runTests(testFunction);
    return 0;
}