#include <stdio.h>
#include <stdint.h>

// Macro to define a struct type with specific fields
#define DEFINE_STRUCT(name, data_type, bytes) \
typedef struct { \
    data_type data; \
    uint8_t bytes[sizeof(bytes)]; \
} name##Struct;

// Macro to create an instance of the defined struct
#define CREATE_STRUCT(struct_name, value, array) \
static inline struct_name struct_name##Create(value val, const uint8_t array[]) { \
    struct_name s = {val, {array[0], array[1], array[2], array[3]}}; \
    return s; \
}

// Macro to hash the struct and print its data
#define HASH_STRUCT(s) ({ \
    uint32_t h = (uint32_t)(s)->data; \
    for (size_t i = 0; i < sizeof((s)->bytes); ++i) { \
        if (i % 2 == 0) { \
            h += (s)->bytes[i] * 2; \
        } else { \
            h += (s)->bytes[i] / 2; \
        } \
    } \
    h; \
})

// Define a specific struct type using the macros
DEFINE_STRUCT(My, int32_t, {1, 2, 3, 4});
CREATE_STRUCT(My, int32_t, {1, 2, 3, 4});

// Function to print the data of a struct instance
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function pointer type for testing
typedef void (*TestFunc)(int32_t, const uint8_t[4]);

// Test function to initialize an array of structs and perform operations
void runTests(TestFunc func) {
    int32_t vals[] = {10, -10, 300, -300};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        uint8_t arr[] = {1, 2, 3, 4};
        func(vals[i], arr);
    }
}

// Function to be used with the function pointer
void testFunction(int32_t x, const uint8_t y[4]) {
    MyStruct s = MyCreate(x, y);
    printStruct(&s);
    printf("%u\n", HASH_STRUCT(&s));
}

// Main function to demonstrate the usage of structs and function pointers
int main() {
    runTests(testFunction);
    return 0;
}