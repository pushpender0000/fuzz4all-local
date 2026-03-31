#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef uint32_t (*HashFunc)(const MyStruct *);

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32_t hashStructSimple(const MyStruct *s) {
    return (uint32_t)s->data + s->bytes[0] + s->bytes[1] + s->bytes[2] + s->bytes[3];
}

uint32_t hashStructComplex(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

uint32_t calculateTotalHash(MyStruct *arr, size_t count, HashFunc hashFunc) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < count; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashFunc(&arr[i]);
    }
    return totalHash;
}

void initializeArray(MyStruct *arr, size_t count, const uint8_t initialArray[]) {
    for (size_t i = 0; i < count; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arr[i] = createStruct(10 * i, initialArray);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printf("%u\n", hashStructComplex(&s));
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    uint8_t initialArray[] = {1, 2, 3, 4};
    initializeArray(arrayOfStructs, ARRAY_SIZE, initialArray);
    runTests(testFunction);

    // Additional test with function pointer and array manipulation
    HashFunc hashFunc = &hashStructComplex;
    uint32_t totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE, hashFunc);
    printf("Total Hash: %u\n", totalHash);

    return 0;
}