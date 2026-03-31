#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto isSame(T a, U b) -> bool {
    return std::is_same_v<T, U>;
}

template<typename T>
constexpr auto add(T a, T b) -> T {
    if constexpr (std::is_integral_v<T>) {
        return a + b;
    } else {
        std::cout << "Error: Unsupported type for addition." << std::endl;
        return 0;
    }
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
        return a * b;
    } else {
        std::cout << "Error: Unsupported types for multiplication." << std::endl;
        return 0;
    }
}

template<typename T>
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(isSame<decltype(val), double>(val, val)) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}