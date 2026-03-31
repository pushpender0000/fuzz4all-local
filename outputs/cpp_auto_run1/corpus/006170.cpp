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

template<typename T, std::size_t N>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, N));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T>
constexpr auto fibonacci(T n) -> T {
    if (n <= 1) return n;
    T a = 0, b = 1, c;
    for (std::size_t i = 2; i <= n; ++i) {
        c = add(a, b);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    constexpr int a = fibonacci<5>();
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    constexpr std::size_t n = fibonacci<fibonacci<3>()>();
    auto totalSum = sumVector<double, n>(nestedVector[0]);

    std::cout << totalSum << std::endl;
}