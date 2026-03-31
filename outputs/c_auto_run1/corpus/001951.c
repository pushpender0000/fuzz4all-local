#include <stdio.h>
#include <stdint.h>

// Macro to calculate the factorial of a number statically
#define FACTORIAL(n) ((n) > 1 ? (n) * FACTORIAL((n) - 1) : 1)

typedef struct {
    uint64_t value;
} FactorialStruct;

// Function to calculate factorial using the struct
FactorialStruct calculateFactorial(uint8_t n) {
    FactorialStruct result;
    if (n == 0 || n == 1) {
        result.value = 1;
    } else {
        uint64_t fact = 1;
        for (uint8_t i = 2; i <= n; ++i) {
            fact *= i;
        }
        result.value = fact;
    }
    return result;
}

// Function to print the factorial of a number
void printFactorial(uint8_t n) {
    FactorialStruct f = calculateFactorial(n);
    printf("%d! = %llu\n", n, f.value);
}

// Function pointer type for functions that take uint8_t and return FactorialStruct
typedef FactorialStruct (*FactorialFunc)(uint8_t);

// Function to use the function pointer to calculate factorial
void runFactorialFunction(FactorialFunc func, uint8_t n) {
    FactorialStruct result = func(n);
    printf("%d! = %llu\n", n, result.value);
}

int main() {
    // Test the macros and functions with different values
    printFactorial(5);
    runFactorialFunction(calculateFactorial, 6);

    // Function pointer usage
    FactorialFunc factorialPtr = calculateFactorial;
    runFactorialFunction(factorialPtr, 7);

    return 0;
}