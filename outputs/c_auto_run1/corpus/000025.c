#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t integer;
    uint16_t smallInt;
    double largeFloat;
} ComplexStruct;

#define ARRAY_SIZE 50
ComplexStruct array[ARRAY_SIZE];

void initialize(int index, int32_t value) {
    array[index].integer = value;
    array[index].smallInt = (uint16_t)(value % UINT16_MAX);
    array[index].largeFloat = (double)value * 0.1;
}

ComplexStruct* getElement(int index) {
    return &array[index];
}

void printHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ComplexStruct *elem = getElement(i);
        totalHash += (uint32_t)(elem->integer + elem->smallInt + (uint16_t)elem->largeFloat);
    }
    printf("%u\n", totalHash);
}

void (*printFuncPtr)(void) = printHash;

int main() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        initialize(i, i * 10);
    }
    printFuncPtr();
    return 0;
}