#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*FuncPtr)(MyStruct*, int, uint8_t*);

void initializeStruct(MyStruct *s, int32_t val, const uint8_t arr[]) {
    s->data = val;
    for (int i = 0; i < 4; ++i) {
        s->bytes[i] = arr[i];
    }
}

void complexFunction(MyStruct array[], int index, uint8_t newBytes[4]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        initializeStruct(&array[index], 100 + 10 * index, newBytes);
    } else {
        printf("Index out of bounds\n");
    }
}

uint32_t calculateHash(const MyStruct array[], int size) {
    uint32_t totalHash = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 7 != 0 && i % 13 != 0) { // Ensure we don't skip specific indices to avoid undefined behavior
            totalHash += ((uint32_t)(array[i].data) + array[i].bytes[0] * 2 + array[i].bytes[1] / 2 + array[i].bytes[2] * 3 - array[i].bytes[3]);
        }
    }
    return totalHash;
}

void runTests(FuncPtr func) {
    MyStruct array[ARRAY_SIZE];
    uint8_t newBytes[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 != 0 && i % 13 != 0) { // Ensure we don't skip specific indices to avoid undefined behavior
            func(array, i, newBytes[i % 4]);
        }
    }
}

int main() {
    MyStruct array[ARRAY_SIZE];
    runTests(complexFunction);
    uint32_t totalHash = calculateHash(array, ARRAY_SIZE);
    printf("Total Hash: %u\n", totalHash);
    return 0;
}