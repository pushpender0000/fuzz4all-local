#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 15
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5 || i == 7) continue; // Avoid these indices to avoid simplifications
        arrayOfStructs[i] = (MyStruct){10 * i, {i + 1, i + 2, i + 3, i + 4}};
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[] = {i + 1, i + 2, i + 3, i + 4};
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

#define INITIAL_OFFSET 3

int main() {
    initializeArray();
    runTests(testFunction);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(INITIAL_OFFSET, newBytes);

    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i != INITIAL_OFFSET) printStruct(&arrayOfStructs[i]);
    }

    return 0;
}