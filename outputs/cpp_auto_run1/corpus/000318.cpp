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

template<typename T, typename U>
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
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
void nestedLambda(const std::vector<std::vector<T>>& vec1, const std::vector<std::vector<U>>& vec2) {
    auto multiply = [](auto a, auto b) -> decltype(auto) { return a * b; };
    int result = 0;
    for_each(vec1.begin(), vec1.end(), [&](const std::vector<T>& subVec1) {
        for_each(subVec1.begin(), subVec1.end(), [&](auto val1) {
            if constexpr (std::is_arithmetic_v<decltype(val1)> && std::is_arithmetic_v<U>) {
                result += multiply(static_cast<T>(val1 * 2), static_cast<U>(3));
            }
        });
    });
    for_each(vec2.begin(), vec2.end(), [&](const std::vector<U>& subVec2) {
        for_each(subVec2.begin(), subVec2.end(), [&](auto val2) {
            if constexpr (std::is_arithmetic_v<decltype(val2)> && std::is_arithmetic_v<T>) {
                result += multiply(static_cast<T>(2), static_cast<U>(val2 * 3));
            }
        });
    });
    std::cout << result << std::endl;
}

int main() {
    constexpr int size = 5;
    std::vector<std::vector<int>> nestedVector1(size, std::vector<int>(size, 1));
    std::vector<std::vector<double>> nestedVector2(size, std::vector<double>(size, 2.0));

    nestedLambda(nestedVector1, nestedVector2);
}