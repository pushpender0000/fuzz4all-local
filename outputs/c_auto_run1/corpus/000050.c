#include <stdio.h>
#include <stdint.h>

// Define a complex struct
typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct;

// Macro to calculate the size of the struct
#define SIZEOF_MYSTRUCT (sizeof(MyStruct))

// Inline function to initialize a MyStruct instance
static inline void initStruct(MyStruct *s, int32_t val, const uint8_t arr[4]) {
    s->a = val;
    for (int i = 0; i < 4; ++i) {
        s->b[i] = arr[i];
    }
}

// Inline function to print the value of a MyStruct instance
static inline void printStruct(const MyStruct *s) {
    printf("%d\n", s->a);
}

// Function to hash the contents of a MyStruct instance
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->a;
    for (int i = 0; i < 4; ++i) {
        h += s->b[i];
    }
    return h;
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
    TestFunc funcs[] = {printStruct, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    // Additional functions to stress the compiler
    void complexOperation(const MyStruct *s1, const MyStruct *s2) {
        printStruct(s1);
        printf("%d\n", hashStruct(s1));
        printStruct(s2);
        printf("%d\n", hashStruct(s2));
    }

    void anotherComplexOperation(const MyStruct *s, int32_t val) {
        MyStruct sCopy;
        initStruct(&sCopy, val, (uint8_t[4]){0});
        printStruct(&sCopy);
        printf("%d\n", hashStruct(&sCopy));
    }

    // Test the additional functions
    complexOperation(&structs[0], &structs[1]);
    anotherComplexOperation(&structs[2], -500);

    return 0;
}