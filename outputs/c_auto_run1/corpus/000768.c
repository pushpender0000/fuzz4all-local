#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i].data = 10 * i;
        for (int j = 0; j < 4; ++j) {
            arrayOfStructs[i].bytes[j] = initialArray[j];
        }
    }
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

typedef void (*TestFunc)(int32_t, uint8_t*);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 150, -150};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[4] = {static_cast<uint8_t>(i), static_cast<uint8_t>(i+1), static_cast<uint8_t>(i+2), static_cast<uint8_t>(i+3)};
        func(vals[i], arr);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        uint8_t newBytes[4] = {1, 2, 3, 4};
        arrayOfStructs[offset].data = 100 + 10 * offset;
        for (int i = 0; i < 4; ++i) {
            arrayOfStructs[offset].bytes[i] = newBytes[i];
        }
    } else {
        printf("Offset out of bounds\n");
    }
}

void stressTest() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    complexFunction(ARRAY_SIZE / 2);
    uint32_t newTotalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == ARRAY_SIZE / 2) {
            newTotalHash += hashStruct(&arrayOfStructs[i]);
        } else {
            newTotalHash += hashStruct(&arrayOfStructs[i]);
        }
    }
    printf("Updated Total Hash: %u\n", newTotalHash);
}

int main() {
    stressTest();
    return 0;
}