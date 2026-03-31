#include <stdio.h>
#include <stdint.h>

// Define a macro for complex calculations within a struct
#define COMPLEX_CALC(a, b) ((a)->data * (b)->bytes[0] + (a)->data / (b)->bytes[1])

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct with given values
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

typedef void (*TestFunc)(MyStruct*, MyStruct*);

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with a function pointer
void runTests(TestFunc func, MyStruct arrayOfStructs[]) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(&CREATESTRUCT(vals[i], arr[i]), &CREATESTRUCT(vals[i] * -1, arr[i]));
    }
}

// Function to test the function pointer usage
void testFunction(MyStruct *s1, MyStruct *s2) {
    int32_t complexVal = COMPLEX_CALC(s1, s2);
    printf("%d\n", complexVal);
}

#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs with complex conditions
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

// Function to print the structs in the array with complex conditions
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

int main() {
    initializeArray();
    runTests(testFunction, arrayOfStructs);
    return 0;
}