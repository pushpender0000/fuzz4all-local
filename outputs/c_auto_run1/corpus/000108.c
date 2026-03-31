#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t id[4];
} MyStruct;

#define MAX_STRUCTS 10
#define INITIAL_VALUE 50

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.id[i] = arr[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->id[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexOperation() {
    int32_t vals[] = {-1, -2, -3, -4};
    uint8_t arr[][4] = {{1}, {2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

void stressTestGCC() {
    int32_t vals[] = {-INITIAL_VALUE, -INITIAL_VALUE + 10, -INITIAL_VALUE + 20, -INITIAL_VALUE + 30};
    uint8_t arr[][4] = {{1}, {2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = createStruct(vals[i], arr[i]);
        printStruct(&s);
        printf("%u\n", hashStruct(&s));
    }
}

int main() {
    runTests(testFunction);
    complexOperation();
    stressTestGCC();
    return 0;
}