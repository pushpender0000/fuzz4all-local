#include <stdio.h>

// Macro for calculating Fibonacci numbers
#define FIB(n) (fib_inline(n))

// Inline function to calculate Fibonacci numbers
static inline int fib_inline(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Typedef for function pointer type
typedef void (*func_ptr)(void);

// Function to create a struct with Fibonacci numbers up to 10
struct FibStruct {
    int fib[10];
};

// Function to initialize the FibStruct and populate it with Fibonacci numbers
static inline struct FibStruct initFibStruct() {
    struct FibStruct fs;
    for (int i = 0; i < 10; ++i) {
        fs.fib[i] = FIB(i);
    }
    return fs;
}

// Function to print the Fibonacci numbers in the struct
void printFibs(const struct FibStruct *fs) {
    for (int i = 0; i < 10; ++i) {
        printf("%d ", fs->fib[i]);
    }
    printf("\n");
}

// Function to demonstrate function pointer usage
void callFunction(func_ptr func) {
    if (func != NULL) {
        func();
    }
}

// Main function demonstrating all constructs
int main() {
    struct FibStruct fs = initFibStruct();
    printFibs(&fs);

    // Function pointer to the same function
    func_ptr fp = (func_ptr)printFibs;
    callFunction(fp);

    return 0;
}