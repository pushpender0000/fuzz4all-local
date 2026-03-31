#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

#define MAX_COMPLEXITY 100

typedef struct {
    int32_t data;
    uint8 bytes[4];
} ComplexStruct;

ComplexStruct createComplexStruct(int32_t val, const uint8 arr[]) {
    ComplexStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32 hashComplexStruct(const ComplexStruct *s) {
    uint32 h = (uint32)(s->data >> 8);
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i] << (i * 4);
    }
    return h;
}

#define INITIAL_VALUE 10

void generateRandomBytes(uint8 arr[]) {
    for (int i = 0; i < 4; ++i) {
        arr[i] = rand() % 256;
    }
}

typedef void (*ComplexFunc)(int32_t, uint8[]);

void runTests(ComplexFunc func) {
    int32_t vals[] = {INITIAL_VALUE, -INITIAL_VALUE};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8 randomBytes[4];
        generateRandomBytes(randomBytes);
        func(vals[i], randomBytes);
    }
}

void testFunction(int32_t x, uint8 y[4]) {
    ComplexStruct s = createComplexStruct(x, y);
    printf("%u\n", hashComplexStruct(&s));
}

#define ARRAY_SIZE 10
ComplexStruct arrayOfComplexStructs[ARRAY_SIZE];

void initializeArray() {
    uint8 initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfComplexStructs[i] = createComplexStruct(INITIAL_VALUE * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%u\n", hashComplexStruct(&arrayOfComplexStructs[i]));
    }
}

uint32 calculateTotalHash() {
    uint32 totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashComplexStruct(&arrayOfComplexStructs[i]);
    }
    return totalHash;
}

uint32 calculateTotalHashFromData() {
    uint32 totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ComplexStruct s = arrayOfComplexStructs[i];
        totalHash += hashComplexStruct(&s);
    }
    return totalHash;
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32 totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    printf("Total Hash from Data: %u\n", calculateTotalHashFromData());
    return 0;
}