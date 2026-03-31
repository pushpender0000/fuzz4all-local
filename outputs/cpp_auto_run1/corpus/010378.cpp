#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>

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

template<typename T, typename... Args>
constexpr auto sum_args(Args... args) -> T {
    return (args + ...);
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    constexpr int x = 3;
    constexpr int y = 4;
    auto hypotenuse = [](auto a, auto b) {
        static_assert(std::is_arithmetic_v<decltype(a)> && std::is_arithmetic_v<decltype(b)>, "Arguments must be arithmetic types");
        return std::sqrt(add(multiply(a, a), multiply(b, b)));
    }(x, y);

    std::cout << result + static_cast<int>(hypotenuse) << std::endl;
}