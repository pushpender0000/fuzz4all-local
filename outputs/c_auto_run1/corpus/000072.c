#include <stdio.h>

#define ARRAY_SIZE 100

typedef struct {
    int data[ARRAY_SIZE];
} ArrayStruct;

#define INITIALIZE(arr) for (int i = 0; i < ARRAY_SIZE; i++) arr.data[i] = 10 + i
#define SUM(arr, result) do { result = 0; for (int i = 0; i < ARRAY_SIZE; i++) result += arr.data[i]; } while (0)

typedef int (*SumFunc)(const ArrayStruct *);

inline int sumArrayDirectly(const ArrayStruct *arr) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += arr->data[i];
    }
    return sum;
}

void printSumWithCallback(const ArrayStruct *arr, SumFunc callback) {
    int result;
    SUM(arr, result); // Using the macro to calculate and store the result
    printf("%d\n", result); // Printing the result
}

int main() {
    ArrayStruct myArray;
    INITIALIZE(myArray); // Initializing the array using the macro
    printSumWithCallback(&myArray, sumArrayDirectly); // Using function pointer and macro in callback
    return 0;
}