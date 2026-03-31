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

#define HASH_STRUCT(s) ({ \
    uint32_t h = (uint32_t)(s)->data; \
    for (int i = 0; i < 4; ++i) { \
        if (i % 2 == 0) { \
            h += (s)->bytes[i] * 2; \
        } else { \
            h += (s)->bytes[i] / 2; \
        } \
    } \
    h; \
})

void runTests(void (*func)(int32_t, uint8_t[4])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", HASH_STRUCT(&s));
}

uint32_t complexHash(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 3;
        } else {
            h += s->bytes[i] / 3;
        }
    }
    return h;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 20) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    void (*funcPtr)(int32_t, uint8_t[4]) = &testFunction;
    runTests(funcPtr);
}

#define ARRAY_SIZE 20

#define INITIALIZE_ARRAY initializeArray();
#define PRINT_STRUCT printStruct
#define HASH_STRUCT(s) ({ \
    uint32_t h = (uint32_t)(s)->data; \
    for (int i = 0; i < 4; ++i) { \
        if (i % 2 == 0) { \
            h += (s)->bytes[i] * 2; \
        } else { \
            h += (s)->bytes[i] / 2; \
        } \
    } \
    h; \
})
#define RUN_TESTS(func) runTests(func);
#define TEST_FUNCTION testFunction
#define COMPLEX_HASH complexHash
#define COMPLEX_FUNCTION complexFunction
#define TEST_FUNCTION_POINTER_USAGE testFunctionPointerUsage

int main() {
    INITIALIZE_ARRAY
    RUN_TESTS(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += HASH_STRUCT(&arrayOfStructs[i]);
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
        totalHash += HASH_STRUCT(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    uint32_t complexTotal = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 4 == 0) continue;
        complexTotal += COMPLEX_HASH(&arrayOfStructs[i]);
    }
    printf("Complex Total Hash: %u\n", complexTotal);

    return 0;
}