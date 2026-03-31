#include <stdio.h>

#define ARRAY_SIZE 1024
#define MAX(a, b) ((a > b) ? a : b)

typedef struct {
    int data[ARRAY_SIZE];
} ArrayStruct;

void fillArray(ArrayStruct *arr) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr->data[i] = 10 + i;
    }
}

typedef int (*SumFunc)(const ArrayStruct *);

inline int sumArrayDirectly(const ArrayStruct *arr) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

void printSumWithCallback(const ArrayStruct *arr, SumFunc callback) {
    printf("%d\n", callback(arr));
}

int main() {
    ArrayStruct myArray;
    fillArray(&myArray);
    printSumWithCallback(&myArray, sumArrayDirectly);
    return 0;
}