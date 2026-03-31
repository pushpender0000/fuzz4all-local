#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t data;
    uint8_t id[4];
} Item;

#define ITEM_COUNT 100
#define INITIAL_DATA 50

Item create_item(int32_t val, const uint8_t arr[]) {
    Item i;
    i.data = val;
    for (int j = 0; j < 4; ++j) {
        i.id[j] = arr[j];
    }
    return i;
}

uint32_t hash_item(const Item *i) {
    uint32_t h = (uint32_t)i->data;
    for (int j = 0; j < 4; ++j) {
        h += i->id[j];
    }
    return h;
}

void print_item(const Item *i) {
    printf("%d\n", i->data);
}

#define MAX_ITER 1000

typedef void (*ItemFunc)(int32_t, uint8_t[4]);

void run_tests(ItemFunc func) {
    int32_t vals[] = {INITIAL_DATA, -INITIAL_DATA, INITIAL_DATA * 2, -INITIAL_DATA * 2};
    uint8_t arr[][4] = {{0}, {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

void complex_operation() {
    Item items[ITEM_COUNT];
    uint8_t initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ITEM_COUNT; ++i) {
        items[i] = create_item(INITIAL_DATA * i, initialArray);
    }
    uint32_t totalHash = 0;
    for (int i = 0; i < ITEM_COUNT; ++i) {
        totalHash += hash_item(&items[i]);
    }
    printf("%u\n", totalHash);
}

void nested_complex_operation() {
    Item nestedItems[MAX_ITER];
    uint8_t innerInitialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < MAX_ITER; ++i) {
        nestedItems[i] = create_item(INITIAL_DATA * i, innerInitialArray);
    }
    uint32_t nestedTotalHash = 0;
    for (int i = 0; i < MAX_ITER; ++i) {
        nestedTotalHash += hash_item(&nestedItems[i]);
    }
    printf("%u\n", nestedTotalHash);
}

void testFunction(int32_t x, uint8_t y[4]) {
    Item item = create_item(x, y);
    print_item(&item);
    printf("%u\n", hash_item(&item));
}

int main() {
    run_tests(testFunction);
    complex_operation();
    nested_complex_operation();
    return 0;
}