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
            result += multiply(val, add(1, -1)); // Ensure no overflow or underflow with addition and multiplication
        } else if constexpr(IsSame<decltype(val), double>::value) {
            result += multiply(val, 2.0); // Stress constant expression evaluation in templates
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return T{}; // Return default value for unsupported types
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum_result = add(a, -a); // Ensure no overflow or underflow with addition and subtraction

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    auto total_sum = sum_vector(nestedVector[0]); // Stress template instantiation and constexpr usage in function

    std::cout << static_cast<int>(total_sum) << std::endl; // Ensure deterministic output by casting to int
}