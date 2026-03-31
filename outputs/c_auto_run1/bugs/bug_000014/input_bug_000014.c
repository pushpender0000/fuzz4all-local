#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 200

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void createStructArray(MyStruct array[], int32_t val, const uint8_t arr[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = (MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}};
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
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

uint32_t calculateTotalHash(const MyStruct array[], int size) {
    uint32_t totalHash = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&array[i]);
    }
    return totalHash;
}

void runTests(TestFunc func, MyStruct array[]) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        MyStruct s = (MyStruct){100 + 10 * offset, newBytes};
        printf("Updated struct at %d: %d\n", offset, s.data);
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    createStructArray(arrayOfStructs, 0, (uint8_t[]){1, 2, 3, 4});

    runTests(testFunction, arrayOfStructs);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Initial Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Updated Total Hash after complex function: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTests((TestFunc)testFunctionWithPointer, arrayOfStructs);
    printf("After second set of tests:\n");
    totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}