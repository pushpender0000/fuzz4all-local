#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[20];

void initializeArray() {
    for (int i = 0; i < 20; ++i) {
        arrayOfStructs[i] = (MyStruct){.data = (i * 10), .bytes = {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s, int flag) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (flag % 2 == 0) {
            h += s->bytes[i] * flag;
        } else {
            h -= s->bytes[i] / (flag + 1);
        }
    }
    return h;
}

void runTests(int (*func)(const MyStruct *, int)) {
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) continue;
        func(&arrayOfStructs[i], i);
    }
}

int testFunction(const MyStruct *s, int flag) {
    printStruct(s);
    printf("%u\n", hashStruct(s, flag));
    return 12345; // Deterministic output for testing
}

void complexFunction(int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 20) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    int (*funcPtr)(const MyStruct *, int) = &testFunction;
    runTests(funcPtr);
}

#define ARRAY_SIZE 20

#define INITIALIZE_ARRAY initializeArray();
#define PRINT_STRUCT printStruct
#define HASH_STRUCT hashStruct
#define RUN_TESTS runTests
#define TEST_FUNCTION testFunction
#define COMPLEX_FUNCTION complexFunction
#define TEST_FUNCTION_POINTER_USAGE testFunctionPointerUsage

int main() {
    INITIALIZE_ARRAY
    RUN_TESTS(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i], i);
    }
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    COMPLEX_FUNCTION(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break;
        PRINT_STRUCT(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i], i);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    uint32_t complexTotal = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 4 == 0) continue;
        complexTotal += hashStruct(&arrayOfStructs[i], i);
    }
    printf("Complex Total Hash: %u\n", complexTotal);

    return 0;
}