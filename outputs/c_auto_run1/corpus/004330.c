#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 50

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

MyStruct createStruct(int32_t val, uint8_t arr[4]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    return (uint32_t)(s->data) + (s->bytes[0] * 2) + (s->bytes[1] / 2) + (s->bytes[2] * 3) - (s->bytes[3]);
}

void printStructData(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void testFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        MyStruct s = createStruct(100 + 10 * offset, newBytes);
        printStructData(&s);
        printf("%u\n", hashStruct(&s));
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTestsWithPointerAndMacro() {
    uint8_t newBytes[] = {9, 10, 11, 12};
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        testFunction(i, newBytes);
    }
}

int main() {
    runTestsWithPointerAndMacro();
    return 0;
}