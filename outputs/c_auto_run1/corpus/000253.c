#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t *data;
    uint8_t size;
} DynamicArray;

DynamicArray createDynamicArray(uint8_t size, int32_t value) {
    DynamicArray arr;
    arr.size = size;
    arr.data = (int32_t *)malloc(sizeof(int32_t) * size);
    for (uint8_t i = 0; i < size; ++i) {
        arr.data[i] = value + i;
    }
    return arr;
}

void freeDynamicArray(DynamicArray arr) {
    free(arr.data);
}

typedef void (*PrintFunc)(const DynamicArray *);

void printInts(const DynamicArray *arr) {
    for (uint8_t i = 0; i < arr->size; ++i) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

void runPrintFunction(PrintFunc func, const DynamicArray *arr) {
    func(arr);
}

#define ARRAY_SIZE 10

int main() {
    DynamicArray arr = createDynamicArray(ARRAY_SIZE, 5);

    PrintFunc printIntsPtr = &printInts;
    runPrintFunction(printIntsPtr, &arr);

    freeDynamicArray(arr);

    return 0;
}