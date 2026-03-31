#include <stdio.h>

// Macro for calculating factorial
#define FACTORIAL(n) ( \
    n == 0 ? 1 : \
    n == 1 ? 1 : \
    n > 1 ? n * FACTORIAL(n - 1) : \
    0 \
)

// Typedef for a function pointer that takes an integer and returns void
typedef void (*FuncPtr)(int);

// Function to calculate Fibonacci sequence up to a certain number
void fibonacciSequence(int num, FuncPtr printFib) {
    int a = 0, b = 1;
    while (a <= num) {
        if (printFib != NULL) {
            printFib(a);
        }
        int next = a + b;
        a = b;
        b = next;
    }
}

// Function to calculate the sum of digits using recursion and inline function
inline int sumOfDigits(int n) {
    return n == 0 ? 0 : (n % 10) + sumOfDigits(n / 10);
}

void printFibonacciNumber(int num) {
    printf("%d ", num);
}

// Main function to demonstrate usage of macros, typedefs, and function pointers
int main() {
    int fibNum = 21; // Number in Fibonacci sequence to calculate
    fibonacciSequence(fibNum, printFibonacciNumber);
    printf("\nSum of digits of %d is %d\n", FACTORIAL(5), sumOfDigits(FACTORIAL(5)));
    return 0;
}