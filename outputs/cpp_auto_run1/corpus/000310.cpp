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
constexpr auto fibonacci(int n) -> std::enable_if_t<std::is_arithmetic_v<T>, T> {
    if (n <= 1) return static_cast<T>(n);
    T a = fibonacci<T>(n - 1), b = fibonacci<T>(n - 2);
    return add(a, b);
}

int main() {
    constexpr int n = 10;
    auto fib = fibonacci<double>(n);

    std::vector<std::vector<int>> nestedVector;
    for (int i = 0; i < n; ++i) {
        nestedVector.push_back({fibonacci<int>(i), fibonacci<int>(i+1)});
    }

    int result = 0;
    auto calcLambda = [&](const std::vector<int>& vec) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, fib);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
    };

    for_each(nestedVector.begin(), nestedVector.end(), calcLambda);

    std::cout << result << std::endl;
}