#include <stdio.h>
#include <stdint.h>

typedef int32_t MyInt;
typedef uint8_t Byte;

typedef struct {
    MyInt data;
    Byte bytes[4];
} MyStruct;

typedef void (*TestFunc)(MyInt, Byte[4]);

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

MyStruct createStruct(MyInt val, const Byte arr[]) {
    MyStruct s = {val};
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

void initializeArray() {
    Byte initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(MyInt offset, Byte newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests(TestFunc func) {
    MyInt vals[] = {10, -10, 150, -150};
    Byte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(MyInt x, Byte y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

#define MAX_ITERATIONS 1000
void stressTest() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional complex operations for stress testing
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        MyInt offset = rand() % ARRAY_SIZE;
        Byte newBytes[] = {rand() % 256, rand() % 256, rand() % 256, rand() % 256};
        complexFunction(offset, newBytes);
    }

    totalHash = calculateTotalHash();
    printf("Final Total Hash: %u\n", totalHash);
}

int main() {
    stressTest();
    return 0;
}