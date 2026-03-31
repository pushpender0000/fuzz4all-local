#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double precisionData;
    uint8_t byteArray[8];
} ComplexStruct;

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

ComplexStruct createComplexStruct(double precisionVal, const uint8_t byteArr[]) {
    ComplexStruct cs = {precisionVal, {byteArr[0], byteArr[1], byteArr[2], byteArr[3], byteArr[4], byteArr[5], byteArr[6], byteArr[7]}};
    return cs;
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

uint32_t hashComplexStruct(const ComplexStruct *cs) {
    uint32_t h = (uint32_t)(cs->precisionData * 100);
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) {
            h += cs->byteArray[i] * 3;
        } else {
            h += cs->byteArray[i] / 3;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

ComplexStruct arrayOfComplexStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfComplexStructs[i] = createComplexStruct(10.0 * i, initialArray);
    }
}

void printComplexStruct(const ComplexStruct *cs) {
    printf("%f\n", cs->precisionData);
}

void complexFunctionWithPointer(double offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfComplexStructs[(int)offset] = createComplexStruct(100.0 + 10.0 * (int)offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*ComplexFuncPtr)(double, uint8_t[4]);

void runTestsWithPointer(ComplexFuncPtr func) {
    double offsets[] = {10.0, -10.0, 300.0, -300.0};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); ++i) {
        func(offsets[i], arr[i]);
    }
}

void printComplexArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printComplexStruct(&arrayOfComplexStructs[i]);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashComplexStruct(&arrayOfComplexStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    double offset = ARRAY_SIZE / 2.0;
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunctionWithPointer(offset, newBytes);
    printf("After complex function call:\n");
    printComplexArray();

    // Test with function pointer and array manipulation
    runTestsWithPointer(complexFunctionWithPointer);
    printf("After second set of tests:\n");
    printComplexArray();

    return 0;
}