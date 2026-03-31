#include <stdio.h>

// Define a complex macro for stress testing
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int data;
    unsigned char bytes[4];
} MyStruct;

// Inline function to initialize a MyStruct instance
static inline void initMyStruct(MyStruct *ms, int d, unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3) {
    ms->data = d;
    ms->bytes[0] = b0;
    ms->bytes[1] = b1;
    ms->bytes[2] = b2;
    ms->bytes[3] = b3;
}

// Function to print a MyStruct instance
void printMyStruct(const MyStruct *ms) {
    printf("%d\n", ms->data);
}

// Define an array of MyStruct instances
#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs
void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i != 5) {
            initMyStruct(&arrayOfStructs[i], 10 * i, (unsigned char)(i + 1), (unsigned char)(i + 2), (unsigned char)(i + 3), (unsigned char)(i + 4));
        } else {
            arrayOfStructs[i] = (MyStruct){.data = 0, .bytes = {0}}; // Special case for index 5 to avoid UB
        }
    }
}

// Function to hash a MyStruct instance
unsigned int hashStruct(const MyStruct *ms) {
    unsigned int h = (unsigned int)ms->data;
    for (int i = 0; i < 4; ++i) {
        h += ms->bytes[i] * (i + 1);
    }
    return h;
}

// Function prototype for the test function pointer
typedef void (*TestFunc)(int, unsigned char[4]);

// Function to run tests with a function pointer
void runTests(TestFunc func) {
    int values[] = {10, -10, 300, -300};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        unsigned char arr[4] = {2 * i, 3 * i, 4 * i, 5 * i}; // Different byte arrays each time
        func(values[i], arr);
    }
}

// The test function that matches the function pointer signature
void testFunction(int x, unsigned char y[4]) {
    MyStruct s;
    initMyStruct(&s, x, y[0], y[1], y[2], y[3]);
    printMyStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Function to demonstrate complex function usage with bounds checking
void complexFunction(int offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        initMyStruct(&arrayOfStructs[offset], 100 + 10 * offset, (unsigned char)(3 * offset), (unsigned char)(3 * offset + 1), (unsigned char)(3 * offset + 2), (unsigned char)(3 * offset + 3));
    } else {
        printf("Offset out of bounds\n");
    }
}

// Function to use a function pointer for testing
void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

int main() {
    initializeArray();
    runTests(testFunction);
    unsigned int totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    complexFunction(50); // Stress test with different offsets
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) break;
        printMyStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) continue;
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}