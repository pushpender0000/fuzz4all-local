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
constexpr auto sum_vector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += multiply(val, add(val, 1));
        } else if constexpr(IsSame<decltype(val), double>::value) {
            result += multiply(val, add(val, 0.5));
        } else {
            std::cout << "Error: Unsupported type in vector." << std::endl;
            exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(add(a, a))>(b));

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int result = sum_vector(nestedVector[0]);

    std::cout << "Result: " << static_cast<int>(sum) << std::endl;
}