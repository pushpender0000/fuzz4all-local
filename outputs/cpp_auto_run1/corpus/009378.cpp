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

template<typename T, typename U, typename V>
constexpr auto calculateNestedSum(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec, V factor) -> V {
    if constexpr (!IsSame<V, int>::value && !IsSame<V, double>::value) {
        throw std::invalid_argument("Unsupported result type");
    }

    V sum = 0;
    for (const auto& vec : outerVec) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                sum += static_cast<V>(multiply(val, factor));
            } else {
                sum += add(static_cast<V>(val), static_cast<V>(factor));
            }
        }
    }
    return sum;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    std::vector<std::vector<double>> nestedVector{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    auto sumFactor = [](auto a, auto b) { return add(a, b); }(a, static_cast<int>(b));

    int result = calculateNestedSum(nestedVector, std::vector<int>{1, 2, 3}, sumFactor);
    std::cout << result << std::endl;
}