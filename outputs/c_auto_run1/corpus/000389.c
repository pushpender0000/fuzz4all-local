#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t data;
    uint8_t buffer[4];
} ComplexStruct;

#define SIZEOF_COMPLEXSTRUCT (sizeof(ComplexStruct))

static inline void initStruct(ComplexStruct *s, int32_t val, const uint8_t arr[4]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->buffer[i] = arr[i];
    }
}

static inline void printStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->buffer[i];
    }
    return h;
}

typedef void (*TestFunc)(const ComplexStruct *);

void runTests(TestFunc func, const ComplexStruct *s) {
    func(s);
}

int main() {
    int32_t vals[] = {10, -10, 1000, -1000};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    ComplexStruct structs[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initStruct(&structs[i], vals[i], arr[i]);
    }

    TestFunc funcs[] = {printStruct, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    // Additional complexity: Adding a function to manipulate the struct in unexpected ways
    ComplexStruct *ptr = (ComplexStruct *)malloc(sizeof(ComplexStruct));
    initStruct(ptr, -500, (uint8_t[]){13, 14, 15, 16});
    runTests((TestFunc)printStruct, ptr);
    free(ptr);

    return 0;
}