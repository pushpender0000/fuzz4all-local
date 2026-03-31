#include <iostream>
#include <vector>
#include <type_traits>
#include <cstdint>

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
void nestedLoop(const std::vector<std::vector<U>>& vec) {
    T result = 0;
    for (const auto& subVec : vec) {
        if constexpr(IsSame<decltype(subVec[0]), int>::value) {
            for (int val : subVec) {
                result += multiply(val, fibonacci<T>(subVec.size()));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int n = 30;
    auto fib = fibonacci<double>(n);

    std::vector<std::vector<int>> nestedVector(n, std::vector<int>(2));
    for (int i = 0; i < n; ++i) {
        nestedVector[i] = {fibonacci<int>(i), fibonacci<int>(i + 1)};
    }

    nestedLoop<double>(nestedVector);
}