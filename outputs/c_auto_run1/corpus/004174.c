#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define a macro for complex number operations
#define COMPLEX_ABS(a, b) ((a * a + b * b))

typedef struct {
    int32_t real;
    int32_t imag;
} Complex;

typedef void (*ComplexFunc)(Complex *);

// Function to print the complex number
void printComplex(Complex *c) {
    printf("%d + %di\n", c->real, c->imag);
}

// Function to initialize a complex number with given real and imaginary parts
Complex createComplex(int32_t real, int32_t imag) {
    Complex c = {real, imag};
    return c;
}

// Function to perform a set of operations on the complex number using function pointers
void operateOnComplex(Complex *c, ComplexFunc func) {
    func(c);
}

// Function to increment the real and imaginary parts of the complex number
void incrementComplex(Complex *c) {
    c->real += 1;
    c->imag += 1;
}

// Function to calculate the absolute value of the complex number
void absComplex(Complex *c) {
    int32_t absVal = COMPLEX_ABS(c->real, c->imag);
    printf("Absolute Value: %d\n", absVal);
}

// Main function demonstrating the use of complex numbers and function pointers
int main() {
    Complex num1 = createComplex(3, 4);
    ComplexFunc funcs[] = {incrementComplex, absComplex};

    for (int i = 0; i < 2; ++i) {
        operateOnComplex(&num1, funcs[i]);
        printComplex(&num1);
    }

    return 0;
}