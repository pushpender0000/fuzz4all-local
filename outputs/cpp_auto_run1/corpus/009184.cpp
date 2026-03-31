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
constexpr auto divide(T a, U b) -> std::enable_if_t<std::is_arithmetic_v<U>, double> {
    if (b != 0) {
        return static_cast<double>(a) / b;
    } else {
        throw std::runtime_error("Division by zero");
    }
}

template<typename T, typename U>
void nestedTemplate(T a, U b) {
    if constexpr(IsSame<decltype(a), int>::value && IsSame<decltype(b), double>::value) {
        try {
            auto result = add(a, static_cast<decltype(a)>(b));
            std::cout << multiply(result, 2.5f) << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        throw std::invalid_argument("Incorrect types used in nested template instantiation");
    }
}

template<typename T, typename U>
void complexCalculation(T a, U b) {
    if constexpr(std::is_arithmetic_v<U>) {
        auto result = add(a, static_cast<decltype(a)>(b));
        std::cout << multiply(result, 2.5f) << std::endl;
    } else {
        throw std::invalid_argument("Incorrect types used in complex calculation");
    }
}

template<typename T>
void lambdaTemplate(T a) {
    auto lambda = [a](auto b) -> decltype(auto) {
        return add(a, b);
    };

    std::cout << lambda(3.5f) << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    nestedTemplate(a, b);
    try {
        complexCalculation(10, 3.0f);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    lambdaTemplate(5);
}