#include <stdio.h>

// Define a simple structure
typedef unsigned char byte;
typedef signed int s_int;

typedef struct {
    s_int data;
    byte bytes[4];
} MyStruct;

#define ARRAY_SIZE 20
MyStruct arrayOfStructs[ARRAY_SIZE];

// Macro to create a struct instance
#define CREATE_STRUCT(val, arr) ((MyStruct){(val), {(arr)[0], (arr)[1], (arr)[2], (arr)[3]}})

// Function to initialize the array of structures
void initializeArray() {
    byte initialArray[] = {1, 2, 3, 4};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 5 || i == 7 || i == 9) {
            continue;
        }
        arrayOfStructs[i] = CREATE_STRUCT(10 * i, initialArray);
    }
}

// Function to print the data of a struct instance
void printStruct(const MyStruct *s) {
    printf("%d\n", s->data);
}

// Function pointer type
typedef void (*TestFunc)(s_int, byte[4]);

// Test function that uses the function pointer
void runTests(TestFunc func) {
    s_int vals[] = {10, -10, 300, -300};
    byte arr[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        func(vals[i], arr[i]);
    }
}

// Implementation of the function pointer usage
void testFunction(s_int x, byte y[4]) {
    MyStruct s = CREATE_STRUCT(x, y);
    printStruct(&s);
}

// Function to calculate a hash value for a struct instance
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

// Function to print the array of structures
void printArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == 7 || i == 8 || i == 9) {
            break;
        }
        printStruct(&arrayOfStructs[i]);
    }
}

// Function to calculate the total hash of the array of structures
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

// Function to manipulate a specific struct instance in the array
void complexFunction(int offset, byte newBytes[4]) {
    if (offset >= 0 && offset < ARRAY_SIZE) {
        arrayOfStructs[offset] = CREATE_STRUCT(100 + 10 * offset, newBytes);
    } else {
        printf("Offset out of bounds\n");
    }
}

// Loop function to stress the system with struct manipulations
#define MAX_LOOP 30
void loopFunction() {
    for (int i = 0; i < MAX_LOOP; ++i) {
        complexFunction(i % ARRAY_SIZE, (byte[]){i * 2, i * 3, i * 4, i * 5});
    }
}

// Function to demonstrate function pointer usage in a more complex scenario
void functionWithPointer() {
    byte newBytes[] = {9, 10, 11, 12};
    complexFunction(ARRAY_SIZE / 2, newBytes);
    printf("After complex function call:\n");
    printArray();
}

// Main function to initialize the array and run tests
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