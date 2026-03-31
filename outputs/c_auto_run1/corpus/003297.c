#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void initializeArray(MyStruct array[]);
uint32_t calculateTotalHash(const MyStruct array[], size_t size);
void complexFunction(MyStruct array[], int32_t offset, const uint8_t newBytes[4]);
void printStruct(const MyStruct *s);

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeArray(arrayOfStructs);

    // First set of tests using function pointer
    void (*testFunction)(int32_t, uint8_t[4]) = NULL;
    testFunction = [](int32_t x, uint8_t y[4]) {
        MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
        printStruct(&s);
        printf("%u\n", (uint32_t)s.data + (uint32_t)s.bytes[0]);
    };

    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(arrayOfStructs, ARRAY_SIZE / 2, newBytes);

    // Print the array after the first set of tests
    printf("After first set of tests:\n");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        printStruct(&arrayOfStructs[i]);
    }

    uint32_t totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Total Hash after first set: %u\n", totalHash);

    // Second set of tests using function pointer
    testFunction = [](int32_t x, uint8_t y[4]) {
        MyStruct s = {x, {y[0], y[1], y[2], y[3]}};
        printStruct(&s);
        printf("%u\n", (uint32_t)s.data + (uint32_t)s.bytes[1]);
    };

    complexFunction(arrayOfStructs, ARRAY_SIZE / 4, newBytes);

    // Print the array after the second set of tests
    printf("After second set of tests:\n");
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        printStruct(&arrayOfStructs[i]);
    }

    totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Updated Total Hash after second set: %u\n", totalHash);

    return 0;
}

void initializeArray(MyStruct array[]) {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) continue; // Avoid specific indices to avoid undefined behavior
        array[i] = (MyStruct){(int32_t)(10 * i), initialArray};
    }
}

uint32_t calculateTotalHash(const MyStruct array[], size_t size) {
    uint32_t totalHash = 0;
    for (size_t i = 0; i < size; ++i) {
        if (i % 3 == 0) continue; // Skip every third element to avoid simple patterns
        totalHash += array[i].data + array[i].bytes[2];
    }
    return totalHash;
}

void complexFunction(MyStruct array[], int32_t offset, const uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        array[offset] = (MyStruct){100 + 10 * offset, newBytes};
    } else {
        printf("Offset out of bounds\n");
    }
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}