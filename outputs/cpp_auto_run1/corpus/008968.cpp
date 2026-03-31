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

template<typename T, typename U, typename V>
constexpr auto nestedMultiply(T a, U b, V c) -> decltype(multiply(multiply(a, b), c)) {
    return multiply(multiply(a, b), c);
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(a)>(b));

    std::vector<std::vector<float>> nestedVector;
    nestedVector.push_back({1.1f, 2.2f, 3.3f});
    nestedVector.push_back({4.4f, 5.5f, 6.6f});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), float>::value) {
                try {
                    result += static_cast<int>(nestedMultiply(val, sum, 2.0f));
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}