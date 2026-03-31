#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double value;
    char identifier[5];
} AnotherStruct;

#define ARRAY_SIZE 20
MyStruct arrayOfStructs[ARRAY_SIZE];
AnotherStruct anotherArray[ARRAY_SIZE / 2];

void initializeArrays() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = (MyStruct){.data = i * 10, .bytes = {i % 256, (i + 1) % 256, (i + 2) % 256, (i + 3) % 256}};
    }
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        anotherArray[i] = (AnotherStruct){.value = i * 10.5, .identifier = {'A' + i, 'B', 'C', 'D', '\0'}};
    }
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 2;
        } else {
            h -= s->bytes[i] / 2;
        }
    }
    return h;
}

uint32_t hashAnotherStruct(const AnotherStruct *a) {
    uint32_t h = (uint32_t)(a->value);
    for (int i = 0; i < 4; ++i) {
        h += a->identifier[i];
    }
    return h;
}

#define INITIAL_VALUE 100
MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
    return s;
}

void runTests(uint32_t (*hashFunc)(const void*), int indexOffset) {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        printf("%u\n", hashFunc(&arrayOfStructs[i + indexOffset]));
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

void complexFunction(int32_t offset, uint8_t newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = createStruct(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

uint32_t (*testFunctionPointer)(const void*) = &hashStruct;

void testFunctionPointerUsage() {
    runTests(testFunctionPointer, 0);
}

int main() {
    initializeArrays();
    uint32_t totalHashInitial = calculateTotalHash();
    printf("Initial Total Hash: %u\n", totalHashInitial);

    // Additional test with a function pointer and complex manipulation
    uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7) {
            break;
        }
        printf("%d\n", arrayOfStructs[i].data);
    }
    uint32_t totalHashUpdated = calculateTotalHash();
    printf("Updated Total Hash: %u\n", totalHashUpdated);

    return 0;
}