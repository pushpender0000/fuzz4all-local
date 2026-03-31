#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiplyAndAdd(const std::vector<std::vector<T>>& vecInts, const std::vector<std::vector<U>>& vecFloats) {
    int totalInt = 0;
    double totalFloat = 0.0;
    for (const auto& subVecInt : vecInts) {
        for (const auto& valInt : subVecInt) {
            if constexpr(std::is_same_v<decltype(valInt), T>) {
                totalInt += static_cast<int>(valInt * 2);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVecFloat : vecFloats) {
        for (const auto& valFloat : subVecFloat) {
            if constexpr(std::is_same_v<decltype(valFloat), U>) {
                totalFloat += static_cast<double>(valFloat * 3.0);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return totalInt + static_cast<int>(totalFloat);
}

template<typename T>
constexpr void printVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    constexpr int multiplier = 3;
    std::vector<std::vector<double>> nestedVectorDouble = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<std::vector<int>> nestedVectorInt = {{1, 2, 3}, {4, 5, 6}};
    
    auto resultDouble = multiplyAndAdd(nestedVectorInt, nestedVectorDouble);
    if (resultDouble >= 0) {
        std::cout << "Total from mixed types: " << resultDouble << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}