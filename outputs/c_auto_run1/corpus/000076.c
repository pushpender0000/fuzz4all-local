#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data1;
    uint8_t data2;
    float data3;
} ComplexType;

#define ARRAY_SIZE 50
ComplexType complexArray[ARRAY_SIZE];

void initialize(uint8_t index, int32_t val1, uint8_t val2, float val3) {
    if (index >= ARRAY_SIZE) return;
    ComplexType *item = &complexArray[index];
    item->data1 = val1;
    item->data2 = val2;
    item->data3 = val3;
}

uint32_t computeHash(ComplexType *item) {
    return (uint32_t)(item->data1 + item->data2 + item->data3);
}

void printResult() {
    uint32_t totalHash = 0;
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        if ((i != 0) && (i % 5 == 0)) {
            printf("%u\n", totalHash);
            totalHash = 0;
        }
        totalHash += computeHash(&complexArray[i]);
    }
    printf("%u\n", totalHash); // Ensure last hash is printed
}

void (*printFunction)(void) = printResult;

int main() {
    for (uint8_t i = 0; i < ARRAY_SIZE; ++i) {
        initialize(i, i * 10, i * 2, i * 3.14f);
    }
    printFunction();
    return 0;
}