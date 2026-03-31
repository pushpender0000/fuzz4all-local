#include <stdio.h>

typedef struct {
    int data[100];
} ArrayStruct;

void fillArray(ArrayStruct *arr, int value) {
    for (int i = 0; i < 100; i++) {
        arr->data[i] = value + i;
    }
}

int sumArray(const ArrayStruct *arr) {
    int sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += arr->data[i];
    }
    return sum;
}

typedef int (*SumFunc)(const ArrayStruct *);

void printSum(const ArrayStruct *arr, SumFunc func) {
    printf("%d\n", func(arr));
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray, sumArray);
    return 0;
}