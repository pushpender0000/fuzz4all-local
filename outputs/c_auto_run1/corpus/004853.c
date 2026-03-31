#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 1024

typedef struct {
    int32_t data;
    uint8_t bytes[4];
} MyStruct;

typedef struct {
    double value;
    int isSet;
} ConfigOption;

void initializeArray(MyStruct array[], ConfigOption options[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 7 == 0 || i % 13 == 0) {
            continue;
        }
        array[i] = (MyStruct){.data = 10 * i, .bytes = {i % 256, (uint8_t)(i / 2), (uint8_t)(i / 3), (uint8_t)(i / 4)}};
    }
}

void updateConfigOption(ConfigOption options[], int index, double newValue) {
    if (index >= 0 && index < ARRAY_SIZE) {
        options[index].value = newValue;
        options[index].isSet = 1;
    }
}

double getConfigValue(const ConfigOption options[], int index) {
    return (index >= 0 && index < ARRAY_SIZE) ? options[index].value : 0.0;
}

void processStructArray(MyStruct array[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        printf("%d\n", array[i].data);
    }
}

void complexFunction(MyStruct array[], int index, uint8_t newBytes[4]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        array[index] = (MyStruct){.data = 100 + 10 * index, .bytes = {newBytes[0], newBytes[1], newBytes[2], newBytes[3]}};
    } else {
        printf("Offset out of bounds\n");
    }
}

typedef void (*FuncPtr)(MyStruct[], int, uint8_t[4]);

void runTests(FuncPtr func) {
    MyStruct array[ARRAY_SIZE];
    ConfigOption options[ARRAY_SIZE];
    initializeArray(array, options);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i % 5 == 0) {
            updateConfigOption(options, i, (double)(10 * i));
        } else if (i % 7 == 0) {
            func(array, i, (uint8_t[4]){(uint8_t)(i), (uint8_t)(i / 2), (uint8_t)(i / 3), (uint8_t)(i / 4)});
        }
    }
}

int main() {
    MyStruct array[ARRAY_SIZE];
    initializeArray(array, NULL);

    runTests(complexFunction);
    processStructArray(array);

    return 0;
}