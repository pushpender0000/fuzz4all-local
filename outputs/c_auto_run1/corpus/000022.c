#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define a complex struct with nested structures
typedef struct {
    int32_t data;
    uint8_t id;
    struct Inner {
        float value;
        char name[10];
    } inner;
} MyStruct;

#define INIT_STRUCT(s, d, i, v, n) (s = (MyStruct){d, i, {v, n}})

// Inline function to initialize a MyStruct instance with nested structure
static inline void initStruct(MyStruct *s, int32_t data, uint8_t id, float value, const char* name) {
    s->data = data;
    s->id = id;
    strncpy(s->inner.name, name, sizeof(s->inner.name) - 1);
    s->inner.value = value;
}

// Macro to calculate the size of the struct
#define SIZEOF_MYSTRUCT (sizeof(MyStruct))

// Inline function to print the value of a MyStruct instance with nested structure
static inline void printStruct(const MyStruct *s) {
    printf("Data: %d, ID: %hhu, Value: %.2f, Name: %s\n", s->data, s->id, s->inner.value, s->inner.name);
}

// Function to hash the contents of a MyStruct instance with nested structure
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)(s->data + s->id);
    for (int i = 0; i < sizeof(s->inner.name); ++i) {
        h += s->inner.name[i];
    }
    return h;
}

// Function pointer type
typedef void (*TestFunc)(const MyStruct *);

// Function that uses a function pointer to operate on a struct instance with nested structure
void runTests(TestFunc func, const MyStruct *s) {
    func(s);
}

// Main function to create and test multiple instances of MyStruct with nested structure
int main() {
    // Define arrays for initialization
    int32_t data[] = {10, -10, 1000, -1000};
    uint8_t id[] = {1, 2, 3, 4};
    float value[] = {1.1f, 2.2f, 3.3f, 4.4f};
    const char* name[] = {"Alpha", "Beta", "Gamma", "Delta"};

    // Create an array of MyStruct instances for testing with nested structure
    MyStruct structs[4];
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        initStruct(&structs[i], data[i], id[i], value[i], name[i]);
    }

    // Use a function pointer to call the print and hash functions sequentially with nested structure
    TestFunc funcs[] = {printStruct, (TestFunc)hashStruct};
    for (int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
        runTests(funcs[i], &structs[i % 4]);
    }

    return 0;
}