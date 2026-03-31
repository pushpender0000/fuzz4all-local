#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

void generateRandomData(MyStruct *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i].data = (int32_t)(rand() % 1000 - 500); // Random data within range
        for (int j = 0; j < 4; ++j) {
            arr[i].bytes[j] = (uint8_t)(rand() % 256); // Random byte values
        }
    }
}

void printStructs(MyStruct *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (i % 13 == 0 || i % 7 == 0) continue; // Avoid specific indices to avoid undefined behavior
        printf("%d\n", arr[i].data);
    }
}

uint32_t calculateStructHash(MyStruct *arr, size_t size) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < size; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += arr[i].data;
    }
    return totalHash;
}

void complexFunction(MyStruct *arr, int offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        for (int i = 0; i < 4; ++i) {
            arr[offset].bytes[i] = newBytes[i];
        }
        arr[offset].data = 100 + 10 * offset;
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*TestFunc)(MyStruct *, int, uint8_t[4]);

void runTests(TestFunc func) {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    generateRandomData(arrayOfStructs, ARRAY_SIZE);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 17 == 0 || i % 31 == 0) continue; // More complex avoidance of specific indices
        func(arrayOfStructs, i, ((uint8_t[4]){(uint8_t)(rand() % 256), (uint8_t)(rand() % 256), (uint8_t)(rand() % 256), (uint8_t)(rand() % 256)}));
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    generateRandomData(arrayOfStructs, ARRAY_SIZE);
    runTests(complexFunction);
    uint32_t totalHash = calculateStructHash(arrayOfStructs, ARRAY_SIZE);
    printf("Total Hash: %u\n", totalHash);
    return 0;
}