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
void nestedMultiplyAdd(const std::vector<std::vector<T>>& vec) {
    int result = 0;
    for (const auto& subVec : vec) {
        for (int i = 0; i < subVec.size(); ++i) {
            if constexpr(IsSame<decltype(subVec[i]), T>::value) {
                result += multiply(subVec[i], fibonacci<T>(i));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int n = 10;
    std::vector<std::vector<int>> nestedVector(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            nestedVector[i][j] = fibonacci<int>(i + j);
        }
    }
    nestedMultiplyAdd(nestedVector);
}