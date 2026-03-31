#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t arr[4];
} MyStruct;

#define INITIAL_VALUE 10
#define MAX_ITER 500

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val * 2; // Increased complexity by adding multiplication
    for (int i = 0; i < 4; ++i) {
        s.arr[i] = arr[i] + 1; // Increased complexity with addition inside array initialization
    }
    return s;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data); // Print data which is now affected by multiplication and added complexity
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->arr[i] * 2; // Increased complexity with multiplication and addition inside hash calculation
    }
    return h;
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s)); // Print the hashed value which is now more complex due to added operations
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {INITIAL_VALUE, -INITIAL_VALUE}; // Increased complexity by including both positive and negative values
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}}; // Increased complexity with more initial arrays
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complexCalculation() {
    int32_t vals[] = {1, -1}; // Increased complexity by including both positive and negative values
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        for (int j = 0; j < sizeof(vals) / sizeof(vals[0]); ++j) {
            int32_t x = vals[i] * vals[j]; // Increased complexity by multiplication inside nested loop
            uint8_t y[4] = {1, 2, 3, 4}; // Increased initialization complexity with defined values
            testFunction(x, y);
        }
    }
}

int main() {
    runTests(testFunction);
    complexCalculation();
    return 0;
}