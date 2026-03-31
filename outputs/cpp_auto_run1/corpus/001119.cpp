#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr bool isSame(T a, U b) {
    return std::is_same_v<T, U>;
}

template<typename T>
constexpr auto add(T a, T b) -> T {
    if constexpr (std::is_arithmetic_v<T>) {
        return a + b;
    } else {
        std::cerr << "Error: Unsupported type for addition." << std::endl;
        std::terminate();
    }
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
        return a * b;
    } else {
        std::cerr << "Error: Unsupported types for multiplication." << std::endl;
        std::terminate();
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int result = 0;
    for (const auto& vec : nestedVector) {
        for (double val : vec) {
            if constexpr(isSame<decltype(val), double>(val, sum)) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cerr << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}