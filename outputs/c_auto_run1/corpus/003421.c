Here is a more complex C program designed to stress the GCC compiler, focusing on structs, typedefs, macros, and function pointers while ensuring it avoids undefined behavior:

```c
#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define ARRAY_SIZE 500
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

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

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
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

#define HASH_MULTIPLIER 37
uint64_t enhancedHashStruct(const MyStruct *s) {
    uint64_t h = (uint64_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += ((uint64_t)s->bytes[i]) * HASH_MULTIPLIER;
        } else {
            h += ((uint64_t)s->bytes[i]) / HASH_MULTIPLIER;
        }
    }
    return h;
}

void enhancedComplexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTests(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

void deterministicRandomFunction() {
    uint8_t randomBytes[4] = {1, 2, 3, 4}; // Placeholder for a real random function
    int32_t offsets[] = {0, ARRAY_SIZE - 1, (int32_t)(ARRAY_SIZE * 0.75)};
    for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); ++i) {
        complexFunction(offsets[i], randomBytes);
    }
}

void enhancedRandomFunction() {
    uint8_t enhancedBytes[4] = {5, 6, 7, 8}; // Placeholder for a more complex set of bytes
    int32_t enhancedOffsets[] = {10, ARRAY_SIZE - 2, (int32_t)(ARRAY_SIZE * 0.25)};
    for (int i = 0; i < sizeof(enhancedOffsets) / sizeof(enhancedOffsets[0]); ++i) {
        enhancedComplexFunction(enhancedOffsets[i], enhancedBytes);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After modifying middle element:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after modification: %u\n", totalHash);

    runTests(testFunction);
    printf("After second set of tests:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    deterministicRandomFunction();
    printf("