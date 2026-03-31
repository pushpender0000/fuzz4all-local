#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <functional>

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
struct NestedTemplate : public std::vector<std::vector<T>> {};

constexpr auto calculateSum = [](const auto& container) {
    using ElementType = typename decltype(container)::value_type;
    ElementType sum = 0;
    for (const auto& elem : container) {
        if constexpr(std::is_arithmetic_v<ElementType>) {
            sum += elem;
        } else {
            std::cout << "Error: Non-arithmetic type in summation." << std::endl;
            return -1;
        }
    }
    return sum;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    double totalSum = calculateSum(nestedVector);
    if (totalSum != -1) {
        std::cout << multiply(totalSum, sum) << std::endl;
    } else {
        return 1;
    }
}