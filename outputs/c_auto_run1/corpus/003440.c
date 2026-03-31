#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 150

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef uint32_t (*HashFunc)(const MyStruct *);

uint32_t hashStruct(const MyStruct *s) {
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

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define INITIALIZE_STRUCTS() \
    for (int i = 0; i < ARRAY_SIZE; ++i) { \
        if (i % 7 == 0 || i % 13 == 0) { continue; } \
        arrayOfStructs[i] = createStruct(10 * i, initialArray); \
    }

#define PRINT_STRUCTS() \
    for (int i = 0; i < ARRAY_SIZE; ++i) { \
        if (i % 7 == 0 || i % 13 == 0) { break; } \
        printStruct(&arrayOfStructs[i]); \
    }

MyStruct arrayOfStructs[ARRAY_SIZE];
uint8_t initialArray[] = {1, 2, 3, 4};

void initializeArray() {
    INITIALIZE_STRUCTS();
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { continue; }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

uint32_t calculateTotalHashWithPointer() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { continue; }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    complexFunction(ARRAY_SIZE / 2, (uint8_t[]){9, 10, 11, 12});
    printf("After complex function call:\n");
    PRINT_STRUCTS();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    PRINT_STRUCTS();
    totalHash = calculateTotalHashWithPointer();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}