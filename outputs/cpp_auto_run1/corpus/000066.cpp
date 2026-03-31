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
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2, double multiplier) {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic.");
    double total = 0;
    for (const auto& subVec : vec1) {
        for (auto val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
                total += static_cast<double>(val) * multiplier + static_cast<double>(val);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1.0; // Indicate error with a negative result
            }
        }
    }
    for (const auto& val : vec2) {
        total += static_cast<double>(val) * multiplier + static_cast<double>(val);
    }
    return total;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> vec2 = {7, 8, 9};

    auto finalResult = multiplyAndAdd(nestedVector1, vec2, 2.5);
    if (finalResult >= 0) {
        std::cout << static_cast<int>(finalResult) << std::endl; // Ensure output is an integer
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}