#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 50
#define CREATESTRUCT(val, arr) ((MyStruct){val, {arr[0] + 1, arr[1] * 2, arr[2] - 3, arr[3] ^ 4}})

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct array[]) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        array[i] = CREATESTRUCT(10 * i, initialArray);
    }
}

uint32_t calculateTotalHash(MyStruct array[]) {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += ((uint32_t)array[i].data + array[i].bytes[0] * 2 - array[i].bytes[1] / 3 + array[i].bytes[2] * 4 ^ array[i].bytes[3]);
    }
    return totalHash;
}

void complexFunction(MyStruct array[], int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = CREATESTRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = CREATESTRUCT(x, y);
    printStruct(&s);
    printf("%u\n", ((uint32_t)s.data + s.bytes[0] * 2 - s.bytes[1] / 3 + s.bytes[2] * 4 ^ s.bytes[3]));
}

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash(arrayOfStructs);
    printf("Total Hash: %u\n", totalHash);

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
    totalHash = calculateTotalHash(arrayOfStructs);
    printf("Updated Total Hash: %u\n", totalHash);

    return 0;
}