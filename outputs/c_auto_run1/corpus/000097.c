#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t id[4];
} MyStruct;

#define ARRAY_SIZE 100
#define INITIAL_VALUE 5

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.id[i] = arr[i];
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->id[i];
    }
    return h;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void complexOperation() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("%u\n", totalHash);
}

void nestedComplexOperation() {
    MyStruct nestedArray[ARRAY_SIZE];
    uint8_t innerInitialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        nestedArray[i] = createStruct(INITIAL_VALUE * i, innerInitialArray);
    }
    uint32_t nestedTotalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        nestedTotalHash += hashStruct(&nestedArray[i]);
    }
    printf("%u\n", nestedTotalHash);
}

typedef void (*TestFunc)(void);

void runTests(TestFunc func) {
    func();
}

int main() {
    runTests(complexOperation);
    runTests(nestedComplexOperation);
    return 0;
}