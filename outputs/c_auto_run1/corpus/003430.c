#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

void complexFunction(MyStruct array[], size_t size, int32_t offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset].data = 100 + 10 * offset;
        for (int i = 0; i < 4; ++i) {
            array[offset].bytes[i] = (uint8_t)(10 * offset + i);
        }
    } else {
        printf("Offset out of bounds\n");
    }
}

void initializeArray(MyStruct array[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = (MyStruct){10 * i, {i, i + 1, i + 2, i + 3}};
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);

    // Trigger complexFunction with a specific offset to stress test the compiler's handling of function calls and struct manipulation.
    complexFunction(arrayOfStructs, ARRAY_SIZE, ARRAY_SIZE / 2);

    // Output the result after all initializations are done to check for potential memory corruption or undefined behavior issues.
    printf("Resulting data at offset %zu: %d\n", ARRAY_SIZE / 2, arrayOfStructs[ARRAY_SIZE / 2].data);

    return 0;
}