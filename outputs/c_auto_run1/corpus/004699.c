#include <stdio.h>
#include <stdint.h>

typedef uint32_t HashType;

typedef struct {
    int16_t data;
    uint8_t bytes[4];
} MyStruct;

#define HASH(s) ((HashType)(s)->data + (s)->bytes[0] * 2 + (s)->bytes[1] / 2 + (s)->bytes[2] * 3 - (s)->bytes[3])

MyStruct createComplexStruct(int16_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

static inline void complexFunctionInline(MyStruct array[], int16_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 100) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

MyStruct arrayOfStructs[100];

void initializeComplexArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 100; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(10 * i, initialArray);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < 100; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += HASH(&arrayOfStructs[i]);
    }
    return totalHash;
}

void testFunctionWithPointer(int16_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%u\n", HASH(&s));
}

typedef void (*TestFuncPtr)(int16_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int16_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printComplexArray() {
    for (int i = 0; i < 100; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

void complexFunction(int16_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 100) {
        arrayOfStructs[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void initializeArrayWithRandomValues() {
    for (int i = 0; i < 100; ++i) {
        arrayOfStructs[i] = createComplexStruct(10 * i, (uint8_t[]){i % 256, (i + 1) % 256, (i + 2) % 256, (i + 3) % 256});
    }
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHash);

    complexFunction(-50, (uint8_t[]){9, 10, 11, 12});
    printf("After complex function call:\n");
    printComplexArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    initializeArrayWithRandomValues();
    printf("After initializing array with random values:\n");
    printComplexArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after random initialization: %u\n", totalHash);

    return 0;
}