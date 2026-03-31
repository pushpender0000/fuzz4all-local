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
constexpr auto divide(T a, U b) -> std::enable_if_t<!std::is_integral_v<U>, double> {
    return static_cast<double>(a) / b;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector1{{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> nestedVector2{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    int result = 0;
    for (const auto& vec : nestedVector1) {
        if constexpr(!vec.empty()) {
            for (int val : vec) {
                if constexpr(IsSame<decltype(val), int>::value) {
                    result += multiply(val, sum);
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
    }

    for (const auto& vec : nestedVector2) {
        if constexpr(!vec.empty()) {
            for (double val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(multiply(val, sum));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
    }

    std::cout << result << std::endl;
}