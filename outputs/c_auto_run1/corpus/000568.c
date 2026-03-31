#include <stdio.h>

#define ARRAY_SIZE 10
#define MAX_ITER 500

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(i * 10, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

typedef struct {
    int32_t values[MAX_ITER];
    uint8_t hashes[MAX_ITER][4];
} TestData;

void generateTestData(TestData *td) {
    for (int i = 0; i < MAX_ITER; ++i) {
        td->values[i] = i * 10;
        for (int j = 0; j < 4; ++j) {
            td->hashes[i][j] = i + j;
        }
    }
}

void printTestData(const TestData *td) {
    for (int i = 0; i < MAX_ITER; ++i) {
        printf("%d\n", td->values[i]);
    }
}

uint32_t calculateTotalHashFromData(const TestData *td) {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        MyStruct s = createStruct(td->values[i], td->hashes[i]);
        totalHash += hashStruct(&s);
    }
    return totalHash;
}

void runTestsWithData(TestFunc func, const TestData *td) {
    for (int i = 0; i < MAX_ITER; ++i) {
        func(td->values[i], td->hashes[i]);
    }
}

uint32_t complexCalculation() {
    uint32_t sum = 0;
    for (int i = 1; i <= MAX_ITER; ++i) {
        for (int j = 0; j < 4; ++j) {
            MyStruct s = createStruct(i * 10, (uint8_t[]){j, j+1, j+2, j+3});
            sum += hashStruct(&s);
        }
    }
    return sum;
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray();
    runTestsWithData(testFunction, NULL); // Passing NULL to simulate data not yet generated
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    TestData td;
    generateTestData(&td);
    printTestData(&td);
    uint32_t totalHashFromData = calculateTotalHashFromData(&td);
    printf("Total Hash from Data: %u\n", totalHashFromData);

    uint32_t complexSum = complexCalculation();
    printf("Complex Calculation Result: %u\n", complexSum);

    return 0;
}