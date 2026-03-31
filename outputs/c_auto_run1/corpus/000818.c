#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

#define ARRAY_SIZE 100

typedef struct {
    int data;
    uint8 bytes[4];
} MyStruct;

typedef void (*TestFunc)(int, uint8[4]);

MyStruct createStruct(int val, const uint8 arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32 hashStruct(const MyStruct *s) {
    uint32 h = (uint32)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef struct {
    MyStruct array[ARRAY_SIZE];
} StructArray;

void initializeArray(StructArray *sa, int vals[], const uint8 arr[][4]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sa->array[i] = createStruct(vals[i], arr[i]);
    }
}

void printArray(const StructArray *sa) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&sa->array[i]);
    }
}

uint32 calculateTotalHash(const StructArray *sa) {
    uint32 totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&sa->array[i]);
    }
    return totalHash;
}

void runTests(TestFunc func, const StructArray *sa) {
    int vals[] = {10, -10, 100, -100};
    uint8 arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int x, uint8 y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

uint32 complexCalculation() {
    uint32 sum = 0;
    for (int i = 1; i <= 100; ++i) {
        for (int j = 0; j < 4; ++j) {
            MyStruct s = createStruct(i * 10, (uint8[]){j, j+1, j+2, j+3});
            sum += hashStruct(&s);
        }
    }
    return sum;
}

int main() {
    StructArray sa;
    int vals[ARRAY_SIZE];
    uint8 arr[ARRAY_SIZE][4];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        vals[i] = i * 10;
        for (int j = 0; j < 4; ++j) {
            arr[i][j] = i + j;
        }
    }
    initializeArray(&sa, vals, arr);
    runTests(testFunction, &sa);
    uint32 totalHash = calculateTotalHash(&sa);
    printf("Total Hash: %u\n", totalHash);

    uint32 complexSum = complexCalculation();
    printf("Complex Calculation Result: %u\n", complexSum);

    return 0;
}