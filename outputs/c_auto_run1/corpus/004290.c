#include <stdio.h>
#include <stdint.h>

// Define a complex macro for nested structures
#define CREATESTRUCT_COMPLEX(val, arr) ((MyStructComplex){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStructSimple;

typedef struct {
    int64_t longData;
    MyStructSimple nested;
} MyStructComplex;

// Macro to calculate the hash of a complex struct
#define HASH_COMPLEX(s) ((uint32_t)(s)->nested.data + (s)->longData * 2 - (s)->bytes[0] / 2 + (s)->bytes[1])

typedef void (*TestFuncComplex)(int64_t, uint8_t[4]);

// Function to run complex tests with a function pointer
void runTestsComplex(TestFuncComplex func) {
    int64_t longVals[] = {100000, -100000, 300000, -300000};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(longVals) / sizeof(longVals[0]); ++i) {
        func(longVals[i], arr[i]);
    }
}

// Function to test the function pointer usage with complex structs
void testFunctionComplex(int64_t x, uint8_t y[4]) {
    MyStructComplex s = CREATESTRUCT_COMPLEX(x, y);
    printf("%ld\n", s.longData);
    printf("%u\n", HASH_COMPLEX(&s));
}

// Function to initialize an array of complex structs with specific conditions
void initializeArrayComplex() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructsComplex[i] = CREATESTRUCT_COMPLEX(10 * i, initialArray);
    }
}

MyStructComplex arrayOfStructsComplex[50];

// Function to print the structs in the complex array with specific conditions
void printArrayComplex() {
    for (int i = 0; i < 50; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%ld\n", arrayOfStructsComplex[i].longData);
    }
}

// Main function to demonstrate the program
int main() {
    initializeArrayComplex();
    runTestsComplex(testFunctionComplex);
    printArrayComplex();

    return 0;
}