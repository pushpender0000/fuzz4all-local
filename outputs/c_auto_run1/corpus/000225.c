#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

#define INITIAL_VALUE 10
#define MAX_ITER 500

MyStruct createStruct(int32_t val, const uint8_t arr[]) {
    MyStruct s;
    s.data = val;
    for (int i = 0; i < 4; ++i) {
        s.bytes[i] = arr[i];
    }
    return s;
}

uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    for (int i = 0; i < 4; ++i) {
        h += s->bytes[i];
    }
    return h;
}

void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

#define ARRAY_SIZE 10
MyStruct arrayOfStructs[ARRAY_SIZE];

void initializeArray() {
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayOfStructs[i] = createStruct(INITIAL_VALUE * i, initialArray);
    }
}

void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printStruct(&arrayOfStructs[i]);
    }
}

uint32_t calculateTotalHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    return totalHash;
}

typedef void (*TestFunc)(int32_t, uint8_t[4]);

void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, INITIAL_VALUE, -INITIAL_VALUE};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void testFunction(int32_t x, uint8_t y[4]) {
    MyStruct s = createStruct(x, y);
    printStruct(&s);
    printf("%u\n", hashStruct(&s));
}

typedef struct {
    int32_t id;
    double value;
} Item;

Item createItem(int32_t id, double val) {
    Item i;
    i.id = id;
    i.value = val;
    return i;
}

void printItem(const Item *i) {
    printf("%d %.2f\n", i->id, i->value);
}

#define ITEM_COUNT 5
Item arrayOfItems[ITEM_COUNT];

void initializeItems() {
    double initialValues[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    for (int i = 0; i < ITEM_COUNT; ++i) {
        arrayOfItems[i] = createItem(INITIAL_VALUE * i, initialValues[i]);
    }
}

void printAllItems() {
    for (int i = 0; i < ITEM_COUNT; ++i) {
        printItem(&arrayOfItems[i]);
    }
}

double calculateTotalValue() {
    double totalValue = 0.0;
    for (int i = 0; i < ITEM_COUNT; ++i) {
        totalValue += arrayOfItems[i].value;
    }
    return totalValue;
}

int main() {
    initializeArray();
    runTests(testFunction);
    uint32_t totalHash = calculateTotalHash();
    printf("Total Hash: %u\n", totalHash);

    initializeItems();
    printAllItems();
    double totalValue = calculateTotalValue();
    printf("Total Value: %.2f\n", totalValue);

    return 0;
}