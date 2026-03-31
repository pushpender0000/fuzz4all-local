#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 30

typedef struct {
    int64_t data;
    uint8_t bytes[8];
} MyStruct;

typedef void (*TestFunc)(int64_t, const uint8_t[]);

MyStruct createStruct(int64_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]}};
    return s;
}

uint64_t hashStruct(const MyStruct *s) {
    uint64_t h = (uint64_t)s->data;
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 3;
        } else {
            h -= s->bytes[i] / 3;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 5 == 0) {
            arrayOfStructs[i] = createStruct(10 * i - 200, initialArray);
        } else {
            arrayOfStructs[i] = createStruct(10 * i + 200, initialArray);
        }
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0) {
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

uint64_t calculateTotalHash() {
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int64_t offset, const uint8_t newBytes[]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests(TestFunc func) {
    int64_t vals[] = {10, -10, 300, -300, 500, -500, 700, -700};
    const uint8_t arr[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i % 3]);
    }
}

void testFunction(int64_t x, const uint8_t y[]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%lu\n", hashStruct(&s));
}

uint64_t complexCalculation() {
    int64_t sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 2 == 0) {
            sum += arrayOfStructs[i].data;
        } else {
            sum -= arrayOfStructs[i].data;
        }
    }
    return (uint64_t)sum;
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint64_t totalHash = calculateTotalHash();
    printf("Total Hash: %lu\n", totalHash);

    const uint8_t newBytes[] = {9, 10, 11, 12, 13, 14, 15, 16};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %lu\n", totalHash);

    uint64_t calcResult = complexCalculation();
    printf("Complex Calculation Result: %lu\n", calcResult);

    return 0;
}