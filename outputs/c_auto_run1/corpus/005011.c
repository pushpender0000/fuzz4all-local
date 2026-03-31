#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024
#define HASH_MULTIPLIER 7
#define INITIAL_VALUE 1000

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createComplexStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint64_t calculateComplexHash(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = createComplexStruct(INITIAL_VALUE + offset * HASH_MULTIPLIER, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }

    uint64_t hash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        hash += ((uint64_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
    }
    return hash;
}

void testFunctionWithPointer(int32_t x, uint8_t y[4]) {
    MyStruct s = createComplexStruct(x, y);
    printStruct(&s);
    printf("%lu\n", ((uint64_t)(s.data) + s.bytes[0] * 2 + s.bytes[1] / 2 + s.bytes[2] * 3 - s.bytes[3]));
}

typedef void (*TestFuncPtr)(int32_t, uint8_t[4]);

void runTestsWithPointer(TestFuncPtr func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void stressTest() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    MyStruct arrayOfStructs[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createComplexStruct(INITIAL_VALUE + i * HASH_MULTIPLIER, newBytes);
    }
}

int main() {
    stressTest();
    runTestsWithPointer(testFunctionWithPointer);

    // Additional complexity: Nested struct usage and multiple function calls within a loop
    MyStruct nestedArray[2][ARRAY_SIZE];
    for (int i = 0; i < 2; ++i) {
        stressTest();
        calculateComplexHash(nestedArray[i], i * ARRAY_SIZE / 2, newBytes);
    }

    // Print a hash derived from the nested array to ensure complexity is maintained and output is deterministic
    uint64_t nestedHash = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < ARRAY_SIZE; ++j) {
            if (j % 7 == 0 || j % 13 == 0) { // Avoid specific indices to avoid undefined behavior
                continue;
            }
            nestedHash += ((uint64_t)(nestedArray[i][j].data) + nestedArray[i][j].bytes[0] * 2 + nestedArray[i][j].bytes[1] / 2 + nestedArray[i][j].bytes[2] * 3 - nestedArray[i][j].bytes[3]);
        }
    }
    printf("%lu\n", nestedHash);

    return 0;
}