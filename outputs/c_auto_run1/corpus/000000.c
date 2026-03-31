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

int sumArray(const ArrayStruct *arr) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

void printSum(const ArrayStruct *arr) {
    printf("%d\n", sumArray(arr));
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, 10);
    printSum(&myArray);
    return 0;
}