#include <stdio.h>
#include <stdint.h>

typedef int32_t myInt;
typedef uint8_t myByte;

#define ARRAY_SIZE 100

typedef struct {
    myInt data;
    myByte bytes[4];
} MyStruct;

void createComplexStruct(MyStruct *s) {
    s->data = 100;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = (myByte)(i + 1);
    }
}

typedef void (*TestFunc)(myInt, myByte[4]);

void runTests(TestFunc func, int count) {
    myInt vals[] = {10, -10, 300, -300};
    myByte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < count && i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(myInt x, myByte y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        MyStruct s = {10 * i, {(myByte)(i), (myByte)(i+1), (myByte)(i+2), (myByte)(i+3)}};
        arrayOfStructs[i] = s;
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        MyStruct *s = &arrayOfStructs[i];
        uint32_t h = (uint32_t)s->data;
        for (int j = 0; j < 4; ++j) {
            if (j % 2 == 0) {
                h += s->bytes[j] * 2;
            } else {
                h += s->bytes[j] / 2;
            }
        }
        totalHash += h;
    }
    return totalHash;
}

void complexFunction(myInt offset, myByte newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){100 + 10 * offset, {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionWithPointer(myInt x, myByte y[4]) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

typedef void (*TestFuncPtr)(myInt, myByte[4]);

void runTestsWithPointer(TestFuncPtr func, int count) {
    myInt vals[] = {10, -10, 300, -300};
    myByte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < count && i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void printArrayWithPointer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
}

int main() {
    initializeArray();
    runTests(testFunction, 4);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    myByte newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    // Test with function pointer and array manipulation
    runTestsWithPointer(testFunctionWithPointer, 4);
    printf("After second set of tests:\n");
    printArrayWithPointer();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}