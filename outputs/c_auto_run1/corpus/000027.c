#include <stdio.h>

// Define a macro for maximum value calculation
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int data[10];
} IntArray;

// Function to fill the array with values from 0 to 9
void fillArray(IntArray *arr) {
    for (int i = 0; i < 10; i++) {
        arr->data[i] = i;
    }
}

// Function to calculate the sum of elements in the array using a macro trick
#define SUM_ARRAY(arr) ({ \
    int _sum = 0; \
    for (int i = 0; i < 10; i++) { \
        _sum += arr.data[i]; \
    } \
    _sum; \
})

// Function pointer type declaration
typedef int (*SumFunc)(IntArray *);

// Function to print the sum using a function pointer
void printSum(IntArray *arr, SumFunc func) {
    printf("%d\n", func(arr));
}

int main() {
    IntArray myArray;
    fillArray(&myArray);
    
    // Use the macro to calculate the sum and pass it as a function pointer
    printSum(&myArray, SUM_ARRAY);

    return 0;
}