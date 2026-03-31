#include <stdio.h>
#include <stdint.h>

// Define complex struct with nested structures for stress testing
typedef struct {
    int32_t a;
    uint8_t b[4];
} MyStruct1;

typedef struct {
    double c;
    MyStruct1 d;
} NestedStruct;

#define SIZEOF_MYSTRUCT1 (sizeof(MyStruct1))
#define SIZEOF_NESTEDSTRUCT (sizeof(NestedStruct))

// Macro to calculate the size of the nested struct for stress testing
static inline void initNestedStruct(NestedStruct *ns, double val, int32_t a, const uint8_t arr[4]) {
    ns->c = val;
    initStruct(&ns->d, a, arr);
}

// Inline function to initialize a MyStruct1 instance for stress testing
static inline void initStruct(MyStruct1 *s, int32_t val, const uint8_t arr[4]) {
    s->a = val;
    for (int i = 0; i < 4; ++i) {
        s->b[i] = arr[i];
    }
}

// Function to hash the contents of a MyStruct1 instance for stress testing
uint32_t hashStruct(const MyStruct1 *s) {
    uint32_t h = (uint32_t)s->a;
    for (int i = 0; i < 4; ++i) {
        h += s->b[i];
    }
    return h;
}

// Function pointer type for stress testing
typedef void (*TestFunc)(const MyStruct1 *);

// Function that uses a function pointer to operate on a struct instance for stress testing
void runTests(TestFunc func, const MyStruct1 *s) {
    func(s);
}

// Main function to create and test multiple instances of MyStruct1 and NestedStruct for stress testing
int main() {
    // Define arrays for initialization
    int32_t vals[] = {10, -10, 1000, -1000};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // Create an array of MyStruct1 instances for testing
    MyStruct1 structs[4];
    NestedStruct nestedStructs[4];
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        initStruct(&structs[i], vals[i], arr[i]);
        initNestedStruct(&nestedStructs[i], (double)vals[i], vals[i], arr[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially for stress testing
    TestFunc funcs[] = {printStruct, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    // Print the nested struct hash value for verification
    for (int i = 0; i < sizeof(nestedStructs) / sizeof(nestedStructs[0]); ++i) {
        printf("%u\n", hashStruct(&nestedStructs[i].d));
    }

    return 0;
}