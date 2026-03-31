#include <stdio.h>
#include <stdint.h>

// Macro to calculate the size of an array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Typedef for a function pointer type
typedef void (*FuncPtr)(uint32_t);

// Struct definition
typedef struct {
    uint8_t data[4];
} MyData;

// Function to initialize the struct
void initMyData(MyData *d, uint8_t val) {
    for (int i = 0; i < 4; ++i) {
        d->data[i] = val + i;
    }
}

// Function to print the data of the struct
void printMyData(const MyData *d) {
    printf("%u\n", *(uint32_t *)d->data);
}

// Macro to create a complex function using function pointers
#define COMPLEX_FUNC(fptr, val) fptr((val))

// Function that uses the macro and function pointer
void runComplexFunction(FuncPtr func, uint32_t value) {
    MyData data;
    initMyData(&data, value);
    printMyData(&data);
    COMPLEX_FUNC(func, value);
}

// Main function to demonstrate the program
int main() {
    // Function pointer initialization and assignment
    FuncPtr func = &runComplexFunction;

    // Call runComplexFunction with a specific value
    uint32_t testValue = 100;
    runComplexFunction(func, testValue);

    return 0;
}