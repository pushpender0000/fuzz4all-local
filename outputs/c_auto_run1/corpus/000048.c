#include <stdio.h>
#include <stdint.h>

// Define a complex struct with nested structures
typedef struct {
    int32_t data;
    union {
        uint8_t bytes[4];
        struct {
            uint16_t low;
            uint16_t high;
        } shorts;
    } u;
} ComplexStruct;

// Macro to calculate the size of the complex struct
#define SIZEOF_COMPLEXSTRUCT (sizeof(ComplexStruct))

// Inline function to initialize a ComplexStruct instance with random data
static inline void initRandomStruct(ComplexStruct *s) {
    s->data = rand();
    for (int i = 0; i < 4; ++i) {
        s->u.bytes[i] = (uint8_t)(rand() % 256);
    }
}

// Inline function to print the value of a ComplexStruct instance
static inline void printComplexStruct(const ComplexStruct *s) {
    printf("%d\n", s->data);
    for (int i = 0; i < 4; ++i) {
        printf("%u ", s->u.bytes[i]);
    }
    printf("\n");
}

// Function to hash the contents of a ComplexStruct instance
uint32_t hashComplexStruct(const ComplexStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->u.bytes[i];
    }
    return h;
}

// Function pointer type
typedef void (*TestFunc)(const ComplexStruct *);

// Function that uses a function pointer to operate on a struct instance
void runTests(TestFunc func, const ComplexStruct *s) {
    func(s);
}

// Main function to create and test multiple instances of ComplexStruct
int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Define arrays for initialization
    ComplexStruct structs[4];
    for (int i = 0; i < sizeof(structs) / sizeof(structs[0]); ++i) {
        initRandomStruct(&structs[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially
    TestFunc funcs[] = {printComplexStruct, (TestFunc)hashComplexStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    return 0;
}