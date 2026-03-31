#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t *data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t*);

void createStruct(MyStruct *s, int32_t val, uint8_t arr[]) {
    s->data = &val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

#define CREATESTRUCT(val, arr) ((MyStruct){.data = &(val), .bytes = {arr[0], arr[1], arr[2], arr[3]}}))

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printf("%d\n", *s.data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        createStruct(&arrayOfStructs[i], vals[i % 4], arr[i % 4]);
    }
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        createStruct(&arrayOfStructs[offset], 100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printf("%d\n", *s.data);
}

typedef void (*TestFuncPtr)(int32_t, uint8_t*);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        printf("%d\n", *arrayOfStructs[i].data);
    }

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunctionWithPointer);
    printf("After second set of tests:\n");
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        printf("%d\n", *arrayOfStructs[i].data);
    }

    return 0;
}