#include <stdio.h>

typedef int32_t MyInt;
typedef uint8_t ByteArr[4];

typedef struct {
    MyInt data;
    ByteArr bytes;
} MyStruct;

typedef void (*FuncPtr)(MyInt, ByteArr);

#define ARRAY_SIZE 10
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i].data = 10 * i;
        for (int j = 0; j < 4; ++j) {
            arrayOfStructs[i].bytes[j] = (uint8_t)(i + j);
        }
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void runTests(FuncPtr func) {
    MyInt vals[] = {10, -10, 100, -100};
    ByteArr arr[] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(MyInt x, ByteArr y) {
    MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void runTestsWithData(FuncPtr func, const MyStruct *dataArray, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        func(dataArray[i].data, dataArray[i].bytes);
    }
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);
    return 0;
}