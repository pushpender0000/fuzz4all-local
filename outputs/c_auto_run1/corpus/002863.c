#include <stdio.h>
#include <stdint.h>

// Define a complex structure with nested types
typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    MyStruct arr[10];
} MyArray;

// Macro to create a MyStruct instance
#define CREATESTRUCT(val, arr) ((MyStruct){.data = (val), .bytes = {arr[0], arr[1], arr[2], arr[3]}});

// Function to hash the struct
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

// Inline function to initialize an array of MyStruct instances
static inline void initArray(MyStruct arr[], int32_t val, const uint8_t byteArr[]) {
    for (int i = 0; i < 10; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        arr[i] = CREATESTRUCT(val * i, byteArr);
    }
}

// Function pointer usage
void runTests(MyStruct (*func)(int32_t, const uint8_t[])) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        MyStruct s = func(vals[i], arr[i]);
        printf("%u\n", hashStruct(&s));
    }
}

// Main function to test the above constructs and functions
int main() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    MyStruct arrayOfStructs[10];
    initArray(arrayOfStructs, 10, initialArray);

    // Function pointer usage example
    runTests((MyStruct (*)(int32_t, const uint8_t[]))createStruct);

    return 0;
}