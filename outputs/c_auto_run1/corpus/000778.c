#include <stdio.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define ARRAY_SIZE 50
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray(int32_t base) {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        int32_t val = base + 10 * (int32_t)i - 200;
        arrayOfStructs[i] = (MyStruct){val, {uint8_t(i % 4), uint8_t((i + 1) % 4), uint8_t((i + 2) % 4), uint8_t((i + 3) % 4)}};
    }
}

void printStructs() {
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 != 0) {
            printf("%d\n", arrayOfStructs[i].data);
        }
    }
}

uint64_t hashStruct(const MyStruct *s) {
    uint64_t h = s->data;
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            h += s->bytes[i] * 3;
        } else {
            h -= s->bytes[i] / 3;
        }
    }
    return h;
}

uint64_t calculateTotalHash() {
    uint64_t totalHash = 0;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 != 0) {
            totalHash += hashStruct(&arrayOfStructs[i]);
        }
    }
    return totalHash;
}

void complexFunction(int64_t offset, const uint8_t newBytes[]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[(size_t)offset].data = int32_t(100 + 10 * offset);
        for (int i = 0; i < 4; ++i) {
            arrayOfStructs[(size_t)offset].bytes[i] = newBytes[i];
        }
    } else {
        printf("Offset out of bounds\n");
    }
}

void testFunction(int64_t x, const uint8_t y[]) {
    MyStruct s = (MyStruct){x, {y[0], y[1], y[2], y[3]}};
    printf("%d\n", s.data);
}

typedef void (*TestFunc)(int64_t, const uint8_t[]);

void runTests(TestFunc func) {
    int64_t vals[] = {10, -10, 300, -300, 500, -500, 700, -700};
    const uint8_t arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i % 3]);
    }
}

int main() {
    initializeArray(-200);
    runTests(testFunction);
    uint64_t totalHash = calculateTotalHash();
    printf("Total Hash: %lu\n", totalHash);

    const uint8_t newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printStructs();
    totalHash = calculateTotalHash();
    printf("Updated Total Hash: %lu\n", totalHash);

    uint64_t calcResult = 0;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 2 == 0) {
            calcResult += arrayOfStructs[i].data;
        } else {
            calcResult -= arrayOfStructs[i].data;
        }
    }
    printf("Complex Calculation Result: %lu\n", (uint64_t)calcResult);

    return 0;
}