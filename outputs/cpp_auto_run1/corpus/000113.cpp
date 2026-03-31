#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

template<typename T, typename F>
auto transformAndSum(const std::vector<T>& vec, F func) {
    T sum = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            sum += func(val);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return -1; // Indicate error with a negative result
        }
    }
    return sum;
}

int main() {
    constexpr int size = 3;
    std::vector<std::vector<int>> nestedVector(size, std::vector<int>(size, 0));
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            nestedVector[i][j] = i * size + j + 1;
        }
    }

    auto sumElements = [](int val) { return val; };
    int totalSum = transformAndSum(nestedVector, sumElements);

    std::vector<std::vector<double>> doubleNestedVector(size, std::vector<double>(size, 0.0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            doubleNestedVector[i][j] = (i * size + j + 1) * 0.5;
        }
    }

    auto sumDoubles = [](double val) { return val; };
    double totalDoubleSum = transformAndSum(doubleNestedVector, sumDoubles);

    std::cout << "Total Sum: " << totalSum << ", Total Double Sum: " << totalDoubleSum << std::endl;
}