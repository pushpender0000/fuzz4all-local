#include <stdio.h>
#include <stdint.h>

// Define a complex type using typedef
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} ComplexStruct;

// Macro to create a complex struct easily
#define CREATE_STRUCT(val, arr) ((ComplexStruct){.data = (val), .bytes = {arr[0], arr[1], arr[2], arr[3]}})

// Function prototype for the function pointer test
void processStruct(ComplexStruct *s);

// Define a macro to calculate hash with some additional operations
#define HASH_STRUCT(s) ((uint32_t)(s->data + s->bytes[0] * 2 + s->bytes[1] * 3 + s->bytes[2] * 4 + s->bytes[3] * 5))

// Function to process the struct, used with function pointer
void processStruct(ComplexStruct *s) {
    printf("%u\n", HASH_STRUCT(s));
}

// Main processing function that uses a function pointer
void runTests(void (*func)(ComplexStruct*)) {
    ComplexStruct arr[4] = {CREATE_STRUCT(1, {1, 2, 3, 4}), CREATE_STRUCT(2, {5, 6, 7, 8}), CREATE_STRUCT(3, {9, 10, 11, 12}), CREATE_STRUCT(4, {13, 14, 15, 16})};
    for (int i = 0; i < 4; ++i) {
        func(&arr[i]);
    }
}

// Main function to demonstrate the usage of macros and function pointers
int main() {
    void (*testFunc)(ComplexStruct*) = processStruct;
    runTests(testFunc);
    return 0;
}