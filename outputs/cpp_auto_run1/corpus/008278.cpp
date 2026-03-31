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
void nestedMultiplyAndAdd(const T& vec1, const U& vec2) {
    if constexpr (IsSame<T, std::vector<double>>::value && IsSame<U, std::vector<int>>::value) {
        int result = 0;
        for (const auto& val1 : vec1) {
            for (const auto& val2 : vec2) {
                if constexpr(IsSame<decltype(val1), double>::value && IsSame<decltype(val2), int>::value) {
                    result += static_cast<int>(multiply(val1, divide(val1, 3)));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return;
                }
            }
        }
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Incorrect types for nestedMultiplyAndAdd." << std::endl;
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> nestedVector2 = {7, 8, 9};

    nestedMultiplyAndAdd(nestedVector1, nestedVector2);
}