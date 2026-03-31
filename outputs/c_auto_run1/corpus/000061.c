#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t a;
    uint16_t b;
    float c;
} ComplexStruct;

#define MAX_COMPLEX 50

ComplexStruct complexArray[MAX_COMPLEX];

void initComplex(int index, int32_t aVal, uint16_t bVal, float cVal) {
    if (index >= MAX_COMPLEX) return; // Ensure no out-of-bounds write
    complexArray[index].a = aVal;
    complexArray[index].b = bVal;
    complexArray[index].c = cVal;
}

uint32_t calculateHash(ComplexStruct *cs) {
    return (uint32_t)(cs->a + cs->b + (uint16_t)cs->c);
}

void printHash() {
    uint32_t totalHash = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        if (i % 5 == 0 && i != 0) { // Print hash every 5 elements to ensure output is not too short
            printf("%u\n", totalHash);
            totalHash = 0; // Reset for next set of hashes
        }
        totalHash += calculateHash(&complexArray[i]);
    }
}

void (*printFuncPtr)(void) = printHash;

// Macro to initialize complex structures in a loop
#define INIT_COMPLEX_ARRAY \
    do { \
        for (int i = 0; i < MAX_COMPLEX; ++i) { \
            initComplex(i, i * 10, (uint16_t)(i * 20), (float)(i * 3.14)); \
        } \
    } while (0);

// Function to calculate the sum of all hashes in the array
uint32_t sumAllHashes() {
    uint32_t totalSum = 0;
    for (int i = 0; i < MAX_COMPLEX; ++i) {
        totalSum += calculateHash(&complexArray[i]);
    }
    return totalSum;
}

// Function to print the sum of all hashes using a function pointer
void printSumOfHashes() {
    printf("%u\n", sumAllHashes());
}

int main() {
    INIT_COMPLEX_ARRAY // Initialize the complex array
    if (MAX_COMPLEX > 0) {
        ComplexStruct *lastElement = &complexArray[MAX_COMPLEX - 1];
        uint32_t lastHash = calculateHash(lastElement);
        printf("%u\n", lastHash); // Print the hash of the last element
    }
    printFuncPtr(); // Call the function pointer to ensure it calls printHash
    printSumOfHashes(); // Use a different method to print the sum of all hashes
    return 0;
}