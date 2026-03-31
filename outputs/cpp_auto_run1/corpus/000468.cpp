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

template<typename T, typename U>
constexpr auto sumVector(const std::vector<std::pair<T, U>>& vec) -> T {
    T result = 0;
    for (const auto& [val1, val2] : vec) {
        if constexpr(IsSame<decltype(val1), int>::value && IsSame<decltype(val2), int>::value) {
            result += multiply(add(val1, fibonacci<int>(val2)), fibonacci<double>(val2));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

int main() {
    constexpr int n = 30;
    auto fib = fibonacci<double>(n);

    std::vector<std::pair<int, int>> nestedVector;
    for (int i = 0; i < n; ++i) {
        nestedVector.emplace_back(fibonacci<int>(i), fibonacci<int>(i+1));
    }

    std::cout << sumVector(nestedVector) << std::endl;
}