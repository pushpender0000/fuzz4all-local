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
#define PRINT_STRUCT_DATA 1

void initializeArray(MyStruct array[]) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (INITIALIZE_STRUCTS && (i % 5 == 0 || i % 7 == 0)) { // Skip every fifth and seventh element to avoid simple patterns
            continue;
        }
        array[i] = createComplexStruct(10 * i, initialArray);
    }
}

void printStructData(MyStruct array[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (PRINT_STRUCT_DATA && (i % 3 == 0 || i % 9 == 0)) { // Print data only from specific indices to avoid simple patterns
            printf("%d\n", array[i].data);
        }
    }
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

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeComplexArray() {
    initializeArray(arrayOfStructs);
}

int main() {
    initializeComplexArray();
    runTestsWithPointer(testFunctionWithPointer);
#ifdef PRINT_STRUCT_DATA
    printStructData(arrayOfStructs);
#endif
    return 0;
}