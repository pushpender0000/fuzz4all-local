#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define a complex struct
typedef struct {
    int32_t data;
    uint8_t buffer[4];
} MyStruct;

// Macro to calculate the size of the struct
#define SIZEOF_MYSTRUCT (sizeof(MyStruct))

// Inline function to initialize a MyStruct instance
static inline void initStruct(MyStruct *s, int32_t val, const uint8_t arr[4]) {
    s->data = val;
    memcpy(s->buffer, arr, 4);
}

// Macro to print the value of a MyStruct instance
#define PRINTSTRUCT(s) printf("%d\n", (s)->data)

// Inline function to hash the contents of a MyStruct instance
static inline uint32_t hashStruct(const MyStruct *s) {
    return (uint32_t)s->data + s->buffer[0] + s->buffer[1] + s->buffer[2] + s->buffer[3];
}

// Function pointer type
typedef void (*TestFunc)(const MyStruct *);

// Function that uses a function pointer to operate on a struct instance
void runTests(TestFunc func, const MyStruct *s) {
    func(s);
}

// Main function to create and test multiple instances of MyStruct
int main() {
    // Define arrays for initialization
    int32_t vals[] = {10, -10, 1000, -1000};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // Create an array of MyStruct instances for testing
    MyStruct structs[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initStruct(&structs[i], vals[i], arr[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially
    TestFunc funcs[] = {PRINTSTRUCT, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    return 0;
}