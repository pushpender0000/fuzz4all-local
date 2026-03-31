#include <iostream>
#include <vector>
#include <type_traits>

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
constexpr auto multiplyAndAddComplex(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
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
constexpr auto multiplyAndAddMixed(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
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

int main() {
    constexpr int size = 5;
    std::vector<std::vector<int>> nestedVector1(size, std::vector<int>(size, 1));
    std::vector<std::vector<double>> nestedVector2(size, std::vector<double>(size, 2.0));

    auto result = multiplyAndAddComplex(nestedVector1, nestedVector2);
    if (result >= 0) {
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}