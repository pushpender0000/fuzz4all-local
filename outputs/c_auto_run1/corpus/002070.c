#include <stdio.h>
#include <stdint.h>

// Define a macro to calculate the size of an array at runtime
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Macro to initialize a structure with given values
#define INIT_STRUCT(d, b0, b1, b2, b3) ((MyStruct){d, {b0, b1, b2, b3}})

// Function prototype for the function pointer test
void complexFunction(int32_t x, uint8_t y[4]);

// Function pointer type definition
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Define a macro to run tests with different parameters
#define RUN_TESTS(func) do { \
    int32_t vals[] = {10, -10, 300, -300}; \
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}; \
    for (size_t i = 0; i < ARRAY_SIZE(vals); ++i) { \
        func(vals[i], arr[i]); \
    } \
} while (0)

// Implementation of the function to be used with the function pointer
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = INIT_STRUCT(x, y[0], y[1], y[2], y[3]);
    printf("%u\n", hashStruct(&s));
}

// Implementation of a complex function that uses inline assembly for stress testing
void complexFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = INIT_STRUCT(x, y[0], y[1], y[2], y[3]);
    printf("%u\n", hashStruct(&s) + 10);
}

// Function to calculate a hash of the structure (for stress testing type system and optimizer)
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

// Main function to initialize the array and run tests with a function pointer
int main() {
    RUN_TESTS(testFunction);
    return 0;
}