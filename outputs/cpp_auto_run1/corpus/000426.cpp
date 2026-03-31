#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename U>
constexpr auto multiplyAndAdd(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic");
    int total = 0;
    for (const auto& subVec1 : vec1) {
        for (int val1 : subVec1) {
            if constexpr(IsSame<decltype(val1), T>::value && IsSame<decltype(val1), U>::value) {
                total += static_cast<T>(val1 * 2);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    for (const auto& subVec2 : vec2) {
        for (int val2 : subVec2) {
            if constexpr(IsSame<decltype(val2), T>::value && IsSame<decltype(val2), U>::value) {
                total += static_cast<U>(val2 * 3);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return total;
}

template<typename T, typename U>
void printResult(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
    auto result = multiplyAndAdd(vec1, vec2);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}

template<typename T>
constexpr auto sumSquares(const std::vector<T>& vec) {
    static_assert(std::is_arithmetic_v<T>, "Type must be arithmetic");
    T sum = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value || IsSame<decltype(val), double>::value) {
            sum += std::pow(static_cast<T>(val), 2);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return -1; // Indicate error with a negative result
        }
    }
    return sum;
}

template<typename T>
void printSumSquares(const std::vector<T>& vec) {
    auto result = sumSquares(vec);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}

int main() {
    constexpr int size = 5;
    std::vector<int> vec1(size, 1);
    std::vector<double> vec2(size, 2.0);

    printSumSquares(vec1);
    printSumSquares(vec2);
}