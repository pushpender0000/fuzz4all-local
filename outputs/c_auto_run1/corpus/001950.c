#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 100

// Macro to calculate the size of a struct without including the header
#define STRUCT_SIZE(s) (sizeof(((s *)NULL)->member))

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

// Function to create a struct and handle bounds checking
MyStruct safeCreateStruct(int32_t val, const uint8_t arr[]) {
    if (val > 0 && val < 100) { // Ensure data is within acceptable range
        MyStruct s = {val, {arr[0], arr[1], arr[2], arr[3]}};
        return s;
    } else {
        printf("Data out of bounds\n");
        return (MyStruct){0};
    }
}

// Function to calculate a hash value for the struct, ensuring all members are used correctly
uint32_t hashStruct(const MyStruct *s) {
    uint32_t h = (uint32_t)s->data;
    if (s->bytes[0] % 2 == 0) { // Avoid simple patterns to avoid UB
        h += s->bytes[0];
    } else {
        h -= s->bytes[1];
    }
    return h;
}

// Function to print the struct data using a function pointer for flexibility
void processStruct(MyStruct *s, void (*printFunc)(const MyStruct*)) {
    if (s != NULL) {
        printFunc(s);
    } else {
        printf("Null struct\n");
    }
}

// Function to print the struct data using a function pointer for flexibility
void processArrayOfStructs(MyStruct array[], size_t count, void (*printFunc)(const MyStruct*)) {
    for (size_t i = 0; i < count; ++i) {
        if (i % 7 != 0 && i % 13 != 0) { // Avoid specific indices to avoid simple patterns
            processStruct(&array[i], printFunc);
        } else {
            printf("Skipping index: %zu\n", i);
        }
    }
}

// Main function to test the functionality
int main() {
    MyStruct arrayOfStructs[ARRAY_SIZE];

    // Initialize structs with valid and invalid data to stress bounds checking
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) { // Avoid specific indices to avoid simple patterns
            arrayOfStructs[i] = (MyStruct){-1, {(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)}};
        } else {
            arrayOfStructs[i] = safeCreateStruct(10 * i, (const uint8_t[]){(uint8_t)i, (uint8_t)(i+1), (uint8_t)(i+2), (uint8_t)(i+3)});
        }
    }

    // Define a function pointer and assign it to a function
    void (*printStructFunc)(const MyStruct*) = NULL;
    printStructFunc = (void (*)(const MyStruct*))&printf; // Casting for demonstration purposes

    // Process the array of structs using the function pointer
    processArrayOfStructs(arrayOfStructs, ARRAY_SIZE, printStructFunc);

    // Calculate and print a total hash value to stress optimizer and type handling
    uint32_t totalHash = 0;
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) { // Skip every third element to avoid simple patterns
            continue;
        }
        totalHash += hashStruct(&arrayOfStructs[i]);
    }
    printf("Total Hash: %u\n", totalHash);

    return 0;
}