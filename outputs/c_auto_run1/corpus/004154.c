#include <stdio.h>
#include <stdint.h>

typedef int32_t MyInt;
typedef struct {
    MyInt data[10];
} MyStruct;

#define ARRAY_SIZE 10

MyStruct createComplexStruct(const MyInt arr[]) {
    MyStruct s = {{0}};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        s.data[i] = arr[i];
    }
    return s;
}

void complexFunctionInline(MyStruct *s, const MyInt val) {
    if (val > 0 && val < ARRAY_SIZE) {
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            s->data[i] += val + i;
        }
    } else {
        printf("Invalid value\n");
    }
}

typedef void (*TestFunc)(MyStruct*, MyInt);

void testFunctionWithPointer(MyStruct *s, MyInt offset) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        complexFunctionInline(s, s->data[offset]);
    } else {
        printf("Offset out of bounds\n");
    }
}

void runTestsWithPointer(TestFunc func, MyStruct *s) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        func(s, i);
    }
}

MyInt calculateTotalHash(const MyStruct s[], int size) {
    MyInt totalHash = 0;
    for (int i = 0; i < size; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += s[i].data[i % ARRAY_SIZE];
    }
    return totalHash;
}

void initializeComplexArray(MyStruct array[]) {
    MyInt initialArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid undefined behavior
            continue;
        }
        array[i] = createComplexStruct((MyInt[]){initialArray[i], initialArray[i+1], initialArray[i+2], initialArray[i+3]});
    }
}

int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];
    initializeComplexArray(arrayOfStructs);
    runTestsWithPointer(testFunctionWithPointer, arrayOfStructs);

    MyInt totalHash = calculateTotalHash(arrayOfStructs, ARRAY_SIZE);
    printf("Total Hash: %d\n", totalHash);

    return 0;
}