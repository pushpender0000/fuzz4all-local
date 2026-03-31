#include <stdio.h>

#define ARRAY_SIZE 100

typedef struct {
    int data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr, int value) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = value + i;
    }
}

inline int sumArray(const ArrayStruct *arr) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

typedef int (*SumFunc)(const ArrayStruct *);

void printSum(const ArrayStruct *arr, SumFunc func) {
    printf("%d\n", func(arr));
}

#define MAX_VALUE 1000

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, MAX_VALUE);
    printSum(&myArray, sumArray);
    return 0;
}