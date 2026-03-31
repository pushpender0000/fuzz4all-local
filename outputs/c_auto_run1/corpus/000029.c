#include <stdio.h>

typedef struct {
    int data[100];
} ArrayStruct;

#define INIT_VALUE 10
#define ARRAY_SIZE 100

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

typedef int (*SumFunc)(const ArrayStruct *);

void printSum(const ArrayStruct *arr, SumFunc func) {
    printf("%d\n", func(arr));
}

#define MAX_REPEAT 10

int main() {
    ArrayStruct myArray;
    fillArray(&myArray, INIT_VALUE);
    
    for (int i = 0; i < MAX_REPEAT; i++) {
        printSum(&myArray, sumArray);
    }

    return 0;
}