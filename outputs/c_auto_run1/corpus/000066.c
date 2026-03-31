#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t x;
    uint16_t y;
} SmallStruct;

typedef struct {
    SmallStruct a[5];
    float b;
} MediumStruct;

typedef struct {
    MediumStruct c[10];
    double d;
} LargeStruct;

#define ARRAY_SIZE 20
LargeStruct largeArray[ARRAY_SIZE];

void initialize(int index, int32_t xVal, uint16_t yVal) {
    if (index >= ARRAY_SIZE) return; // Ensure no out-of-bounds write
    for (int i = 0; i < 5; ++i) {
        largeArray[index].c[i].a[0] = (SmallStruct){xVal + i, yVal + i};
        largeArray[index].c[i].a[1] = (SmallStruct){xVal - i, yVal - i};
    }
    largeArray[index].d = index * 3.14;
}

uint64_t calculateHash(LargeStruct *ls) {
    uint64_t hash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < 5; ++j) {
            hash += ls->c[i].a[j].x + ls->c[i].a[j].y;
        }
    }
    return hash;
}

void printHash() {
    uint64_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 5 == 0 && i != 0) { // Print hash every 5 elements to ensure output is not too short
            printf("%llu\n", totalHash);
            totalHash = 0; // Reset for next set of hashes
        }
        totalHash += calculateHash(&largeArray[i]);
    }
}

void (*printFuncPtr)(void) = printHash;

int main() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        initialize(i, i * 10, (uint16_t)(i * 20));
    }
    printFuncPtr(); // Call the function pointer to ensure it calls printHash
    return 0;
}