#include <stdio.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define ARRAY_SIZE 1000

typedef struct {
    u8 data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, u8 value) {
    for (u32 i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

u64 sumElement(const u8* elem) {
    return (*elem % 2 == 0) ? *elem * 3 : *elem / 2;
}

u64 accumulateSum(const ArrayStruct *arr, u32 start, u32 end) {
    u64 sum = 0;
    for (u32 i = start; i < end; i++) {
        sum += sumElement(&arr->data[i]);
    }
    return sum;
}

void printAccumulatedSum(const ArrayStruct *arr) {
    printf("%lu\n", accumulateSum(arr, 0, ARRAY_SIZE));
}

typedef u64 (*FuncPtr)(const u8*);

u64 doubleAccumulateSum(const ArrayStruct *arr) {
    FuncPtr func = sumElement;
    return func(&arr->data[0]) * 2 + accumulateSum(arr, 1, ARRAY_SIZE - 1);
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 1);
    printAccumulatedSum(&myArray);
    printf("%lu\n", doubleAccumulateSum(&myArray));
    return 0;
}