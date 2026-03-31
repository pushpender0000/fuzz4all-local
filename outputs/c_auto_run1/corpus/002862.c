#include <stdio.h>
#include <stdint.h>

// Macro for defining a struct with a fixed size array inside
#define ARRAY_SIZE 50
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to create a MyStruct instance
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

// Function to hash the struct for testing purposes
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

#define INITIAL_VALUE 10
#define OFFSET_STEP 5

MyStruct arrayOfStructs[ARRAY_SIZE];

// Function to initialize the array of structs
void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arrayOfStructs[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
}

// Function to print the hash values of the structs in the array
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            break;
        }
        printf("%u\n", hashStruct(&arrayOfStructs[i]));
    }
}

// Function to modify a struct in the array based on an offset
void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(INITIAL_VALUE * offset + OFFSET_STEP, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Typedef for a function pointer that takes two arguments and returns void
typedef void (*TestFunc)(int32_t, uint8_t[4]);

// Function to run tests with different parameters using the function pointer
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Function to test the function pointer usage
void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    printArray();

    // Additional test with complex function call
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();

    return 0;
}