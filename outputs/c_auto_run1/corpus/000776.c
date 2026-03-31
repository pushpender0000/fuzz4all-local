#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;

#define MAX_STRUCTS 30

typedef struct {
    int64_t data;
    byte bytes[4];
} MyStruct;

MyStruct createStruct(int64_t val, const byte arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)(s->data >> 32);
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 3;
        } else {
            h -= s->bytes[i] / 2;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%ld\n", s->data);
}

typedef void (*TestFunc)(int64_t, byte[]);

void runTests(TestFunc func, int64_t startVal, byte arr[][4]) {
    for (int i = 0; i < 5; ++i) {
        func((startVal + i * 10), arr[i]);
    }
}

void testFunction(int64_t x, byte y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

MyStruct arrayOfStructs[MAX_STRUCTS];

void initializeArray() {
    byte initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < MAX_STRUCTS; ++i) {
        if (i == 5 || i == 7 || i == 9) {
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < MAX_STRUCTS; ++i) {
        if (i == 7 || i == 8) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_STRUCTS; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int64_t offset, byte newBytes[4]) {
    if (offset >= 0 && offset < MAX_STRUCTS) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

void optimizeMePlease() {
    int64_t sum = 0;
    for (int i = 0; i < MAX_STRUCTS; ++i) {
        if (i % 2 == 0) {
            sum += arrayOfStructs[i].data;
        } else {
            sum -= arrayOfStructs[i].data;
        }
    }
    printf("Sum of struct data: %ld\n", sum);
}

int main() {
    initializeArray();
    byte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {17, 18, 19, 20}};
    runTests(testFunction, -10, arr);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    byte newBytes[] = {9, 10, 11, 12};
    complexFunction(MAX_STRUCTS / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    optimizeMePlease();

    return 0;
}