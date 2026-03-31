#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 200

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct array[]) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = (MyStruct){10 * i, initialArray};
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
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

void printArray(const MyStruct array[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&array[i]);
    }
}

void runTests(TestFunc func, MyStruct array[]) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

uint32_t calculateTotalHash(const MyStruct array[]) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&array[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray(arrayOfStructs);
    runTests(testFunction, arrayOfStructs);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTests((TestFunc)testFunctionWithPointer, arrayOfStructs);
    printf("After second set of tests:\n");
    printArray(arrayOfStructs);
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}