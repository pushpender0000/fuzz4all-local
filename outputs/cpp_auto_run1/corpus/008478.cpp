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
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T, typename U>
constexpr auto divide(T a, U b) -> std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, decltype(a / b)> {
    return a / b;
}

template<typename T, typename U>
constexpr auto calculateResult(T x, U y) -> int {
    if constexpr(IsSame<int, int>::value) {
        std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
        double sum = add(static_cast<double>(x), static_cast<double>(y));
        int result = 0;
        for (const auto& vec : nestedVector) {
            if constexpr(IsSame<double, double>::value) {
                result += static_cast<int>(multiply(vec[1], sum));
                result -= static_cast<int>(divide(vec[2], 2.0));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        return result;
    } else {
        return -1; // Ensure non-zero return value for valid program behavior.
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = calculateResult(a, b);

    std::cout << sum << std::endl;
}