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

template<typename T, typename U>
constexpr auto divide(T a, U b) -> std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, decltype(a / b)> {
    return a / b;
}

template<typename T, typename U>
struct NestedVector {
    std::vector<T> inner;
    std::vector<NestedVector<T, U>> nested;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedVector<double, float> nv;
    nv.inner.push_back(1.1);
    nv.inner.push_back(2.2);
    nv.inner.push_back(3.3);

    nv.nested.push_back({{4.4, 5.5, 6.6}});
    nv.nested.push_back({{7.7, 8.8, 9.9}});

    int result = 0;
    for (const auto& vec : nv.nested) {
        for (auto val : vec.inner) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}