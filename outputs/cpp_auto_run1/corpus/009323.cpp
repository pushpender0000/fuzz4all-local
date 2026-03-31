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

template<typename T, size_t N>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<T, int>::value) {
            result += static_cast<int>(multiply(val, add(static_cast<T>(1), static_cast<T>(2))));
        } else if constexpr(IsSame<T, double>::value) {
            result += static_cast<int>(multiply(val, add(static_cast<T>(3.0), static_cast<T>(4.0))));
        }
    }
    return result;
}

int main() {
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2}, {3.3, 4.4}};
    auto totalSum = sumVector(nestedVector);
    std::cout << totalSum << std::endl;
}