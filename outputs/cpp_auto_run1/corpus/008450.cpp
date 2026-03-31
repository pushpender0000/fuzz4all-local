#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename U>
auto multiply(const T& a, const U& b) -> decltype(a * b) {
    return a * b;
}

template<typename T, typename U>
void nestedTemplateInstantiation() {
    constexpr T x = 3.14;
    constexpr U y = 2.718;
    auto result = multiply(x, y);
    std::cout << static_cast<int>(result) << std::endl;
}

template<typename T>
void lambdaExample() {
    auto addLambda = [](const T& a, const T& b) -> T {
        return a + b;
    };

    constexpr T a = 5.678;
    constexpr T b = 9.012;
    auto sum = addLambda(a, b);
    std::cout << static_cast<int>(sum) << std::endl;
}

int main() {
    nestedTemplateInstantiation<double, double>();
    lambdaExample<double>();
    return 0;
}