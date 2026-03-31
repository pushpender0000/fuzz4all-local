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

template<typename T>
constexpr auto factorial(T n) -> std::enable_if_t<std::is_integral_v<T>, T> {
    static_assert(n >= 0, "Factorial is not defined for negative numbers");
    T result = 1;
    for (T i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = factorial(a);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    double result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += multiply(val, b);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}