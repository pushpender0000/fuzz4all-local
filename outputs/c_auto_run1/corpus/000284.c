#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    MyStruct *arrayPtr;
    size_t arraySize;
} ArrayWrapper;

#define INITIAL_VALUE 10
#define ARRAY_SIZE 5

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.bytes[i] = arr[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

ArrayWrapper createArrayWrapper() {
    ArrayWrapper wrapper;
    wrapper.arrayPtr = (MyStruct *)malloc(ARRAY_SIZE * sizeof(MyStruct));
    if (!wrapper.arrayPtr) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    wrapper.arraySize = ARRAY_SIZE;
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        wrapper.arrayPtr[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
    return wrapper;
}

void freeArrayWrapper(ArrayWrapper *wrapper) {
    if (wrapper->arrayPtr) {
        for (size_t i = 0; i < wrapper->arraySize; ++i) {
            // Do nothing, just to test memory management
        }
        free(wrapper->arrayPtr);
        wrapper->arrayPtr = NULL;
    }
}

uint32_t calculateTotalHash(const ArrayWrapper *wrapper) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < wrapper->arraySize; ++i) {
        totalHash += hashStruct(&wrapper->arrayPtr[i]);
    }
    return totalHash;
}

void printArray(const ArrayWrapper *wrapper) {
    for (size_t i = 0; i < wrapper->arraySize; ++i) {
        printStruct(&wrapper->arrayPtr[i]);
    }
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
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define MAX_ITER 1000

int main() {
    ArrayWrapper wrapper = createArrayWrapper();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(&wrapper);
    printf("Total Hash: %u\n", totalHash);
    freeArrayWrapper(&wrapper);
    return 0;
}