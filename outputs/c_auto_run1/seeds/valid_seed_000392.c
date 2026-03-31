#include <stdio.h>
#include <stdint.h>

// Macro to calculate a complex hash based on struct members
#define COMPLEX_HASH(s) ((uint32_t)(s)->data * 3 + (s)->bytes[0] - (s)->bytes[1] / 2 + (s)->bytes[2] % 5 + (s)->bytes[3])

// Define a struct with minimal members to ensure complexity in the hash calculation
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to create a struct instance for easy initialization
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0], arr[1], arr[2], arr[3]}})

// Typedef a function pointer type for clarity and ease of use
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to print the data part of a struct instance
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage with a struct instance
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", COMPLEX_HASH(&s));
}

// Function to initialize an array of structs with specific patterns
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < 50; ++i) { // Ensure all elements are initialized
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        MyStruct s = CREATESTRUCT(10 * i, initialArray);
        printf("%d\n", s.data); // Print data part for debugging initialization patterns
    }
}

int main() {
    initializeArray(); // Initialize the array of structs
    runTests(testFunction); // Run tests using the function pointer
    return 0;
}