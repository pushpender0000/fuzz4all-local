#include <stdio.h>

#define ARRAY_SIZE 20

typedef unsigned char byte;
typedef signed int s_int;

typedef struct {
    s_int data;
    byte bytes[4];
} MyStruct;

MyStruct createStruct(s_int val, const byte arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

unsigned int hashStruct(const MyStruct *s) {
    unsigned int h = (unsigned int)s->data;
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

typedef void (*TestFunc)(s_int, byte[4]);

void runTests(TestFunc func) {
    s_int vals[] = {10, -10, 300, -300};
    byte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(s_int x, byte y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    byte initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5 || i == 7 || i == 9) {
            continue;
        }
        arrayOfStructs[i] = createStruct(10 * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7 || i == 8 || i == 9) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

unsigned int calculateTotalHash() {
    unsigned int totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int offset, byte newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

#define MAX_LOOP 30
void loopFunction() {
    for (int i = 0; i < MAX_LOOP; ++i) {
        complexFunction(i % ARRAY_SIZE, (byte[]){i * 2, i * 3, i * 4, i * 5});
    }
}

void functionWithPointer() {
    byte newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
}

int main() {
    initializeArray();
    runTests(testFunction);
    unsigned int totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    // Additional test with a function pointer and complex manipulation
    byte newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHash);

    loopFunction();
    totalHash = calculateTotalHash();
    printf("Final Total Hash after looping: %u\n", totalHash);

    functionWithPointer();

    return 0;
}