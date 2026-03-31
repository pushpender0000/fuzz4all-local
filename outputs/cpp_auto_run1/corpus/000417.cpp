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
auto generateNestedVector(int n) {
    std::vector<std::vector<U>> nestedVector;
    for (int i = 0; i < n; ++i) {
        nestedVector.push_back({fibonacci<T>(i), fibonacci<T>(i + 1)});
    }
    return nestedVector;
}

template<typename T, typename U>
void calculateResult(const std::vector<std::vector<U>>& nestedVector) {
    T result = 0;
    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, fibonacci<T>(vec.size()));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int n = 30;
    auto nestedVector = generateNestedVector<double, int>(n);
    calculateResult<double>(nestedVector);
}