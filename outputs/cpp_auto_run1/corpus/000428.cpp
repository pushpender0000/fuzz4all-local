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
void printResult(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
    auto result = multiplyAndAdd(vec1, vec2);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}

template<typename T>
constexpr auto generateVector(int size, T value) {
    std::vector<std::vector<T>> vec(size, std::vector<T>(size, value));
    return vec;
}

int main() {
    constexpr int size = 10; // Increased size for complexity
    auto nestedVector1 = generateVector(size, 1);
    auto nestedVector2 = generateVector(size, 2.0);

    printResult(nestedVector1, nestedVector2);
}