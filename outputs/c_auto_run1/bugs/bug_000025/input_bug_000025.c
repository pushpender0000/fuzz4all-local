#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 100

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

#define INITIALIZE_STRUCTS 1

void initializeComplexArray(MyStruct array[], int size) {
#ifdef INITIALIZE_STRUCTS
    for (int i = 0; i < size; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        array[i] = createComplexStruct(10 * i, (uint8_t[]){i, i + 1, i + 2, i + 3});
    }
#endif
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printf("%d\n", s.data);
}

void runTestsWithPointer(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

#define COMPLEX_FUNCTION_CALLS 1

void complexFunctionInline(MyStruct array[], int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
#ifdef COMPLEX_FUNCTION_CALLS
    initializeComplexArray(arrayOfStructs, ARRAY_SIZE);
    runTestsWithPointer(testFunctionWithPointer);
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7 || i == 13 || i == 20) continue; // Skipping specific indices to avoid simple patterns
        totalHash += ((uint32_t)(arrayOfStructs[i].data) + (arrayOfStructs[i].bytes[0] * 2) + (arrayOfStructs[i].bytes[1] / 2) + (arrayOfStructs[i].bytes[2] * 3) - (arrayOfStructs[i].bytes[3]));
    }
#endif
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunctionInline(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7 || i == 13 || i == 20) continue; // Skipping specific indices to avoid undefined behavior
        printf("%d\n", arrayOfStructs[i].data);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7 || i == 13 || i == 20) continue; // Skipping specific indices to avoid simple patterns
        totalHash += ((uint32_t)(arrayOfStructs[i].data) + (arrayOfStructs[i].bytes[0] * 2) + (arrayOfStructs[i].bytes[1] / 2) + (arrayOfStructs[i].bytes[2] * 3) - (arrayOfStructs[i].bytes[3]));
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}