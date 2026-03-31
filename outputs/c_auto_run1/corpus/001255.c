#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct arrayOfStructs[20];

// Macro to initialize the array with specific conditions
#define INITIALIZE_ARRAY \
    do { \
        for (int i = 0; i < 20; ++i) { \
            if ((i % 3 != 0 && i % 7 != 0)) { \
                arrayOfStructs[i] = (MyStruct){.data = i * 10, .bytes = {1, 2, 3, 4}}; \
            } \
        } \
    } while (0)

// Function to hash the struct using complex operations
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * (i + 1);
        } else {
            h -= s->bytes[i] / (i + 1);
        }
    }
    return h;
}

// Function to print the struct data, adding complexity with multiple conditions
void printStruct(const MyStruct *s) {
    if (s->data > 0 && s->data % 5 == 0) {
        printf("%d\n", s->data);
    } else {
        printf("Skipped: %d\n", s->data);
    }
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Macro to run tests with function pointer and complex conditions
#define RUN_TESTS(func) \
    do { \
        int32_t vals[] = {10, -10, 300, -300}; \
        for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) { \
            func(vals[i], (uint8_t[4]){1, 2, 3, 4}); \
        } \
    } while (0)

void runTests(TestFunc func) {
    RUN_TESTS(func);
}

// Function to test the function pointer usage and struct manipulation
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = (MyStruct){.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

// Function to manipulate the array of structs with complex conditions and skipping elements
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < 20) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunctionPointerUsage() {
    TestFunc funcPtr = &testFunction;
    runTests(funcPtr);
}

int main() {
    INITIALIZE_ARRAY; // Initialize the array with complex conditions
    runTests(testFunction); // Use function pointer and pass tests
    uint32_t totalHash = 0;
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) continue; // Skip every third element
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash); // Print the total hash after complex operations

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(15, newBytes); // Manipulate a specific index in the array
    for (int i = 0; i < 20; ++i) {
        if (i == 7) break; // Stop after processing the seventh element
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = 0;
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) continue; // Skip every third element again
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Updated Total Hash: %u\n", totalHash); // Print the updated total hash after changes

    return 0;
}