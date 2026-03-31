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

template<typename T>
void printFibVector(const std::vector<std::vector<T>>& vec) {
    int result = 0;
    for (const auto& subVec : vec) {
        if constexpr(IsSame<decltype(subVec[0]), double>::value) {
            for (auto val : subVec) {
                result += static_cast<int>(val);
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

    std::vector<std::vector<double>> nestedVector(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if constexpr(IsSame<decltype(fib), double>::value) {
                nestedVector[i][j] = fibonacci<double>(i + j);
            } else {
                std::cout << "Error: Incorrect type used in initialization." << std::endl;
                return 1;
            }
        }
    }

    printFibVector(nestedVector);
}