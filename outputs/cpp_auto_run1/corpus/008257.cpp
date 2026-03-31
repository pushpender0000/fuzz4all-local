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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            // Skip non-int values for summation
        }
    }
    return result;
}

template<typename T, typename U>
auto sumAndMultiply(const std::vector<T>& vec1, const std::vector<U>& vec2) -> int {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic");
    T sum1 = sumVector(vec1);
    U sum2 = sumVector(vec2);
    return multiply(sum1, sum2);
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = sumAndMultiply(nestedVector[0], nestedVector[1]);
    std::cout << result << std::endl;
}