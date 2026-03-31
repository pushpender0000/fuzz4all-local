#include <stdio.h>

typedef unsigned int uint;

typedef struct {
    int data;
    char bytes[4];
} MyStruct;

#define ARRAY_SIZE 100
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        arrayOfStructs[i] = (MyStruct){.data = 10 * i, .bytes = {i, i + 1, i + 2, i + 3}};
    }
}

uint hashStruct(const MyStruct *s) {
    uint h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h += s->bytes[i] / 2;
        }
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

typedef void (*TestFunc)(int, char[4]);

uint totalHashSum() {
    uint sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        sum += hashStruct(&arrayOfStructs[i]);
    }
    return sum;
}

void modifyElement(int offset, char newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = (MyStruct){.data = 100 + 10 * offset, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTests(TestFunc func) {
    int vals[] = {10, -10, 300, -300};
    char arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int x, char y[4]) {
    MyStruct s = {.data = x, .bytes = {y[0], y[1], y[2], y[3]}};
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint sum = totalHashSum();
    printf("Initial Total Hash Sum: %u\n", sum);

    char newBytes[] = {9, 10, 11, 12};
    modifyElement(ARRAY_SIZE / 2, newBytes);
    printf("After modifying middle element:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }
    sum = totalHashSum();
    printf("Updated Total Hash Sum after modification: %u\n", sum);

    runTests(testFunction);
    printf("After second set of tests:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        printStruct(&arrayOfStructs[i]);
    }
    sum = totalHashSum();
    printf("Updated Total Hash Sum after second set: %u\n", sum);

    return 0;
}