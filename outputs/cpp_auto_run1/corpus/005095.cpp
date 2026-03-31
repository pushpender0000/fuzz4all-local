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
constexpr auto calculateSumAndProduct(T x, U y) -> std::pair<T, decltype(x * y)> {
    constexpr T sum = add(10, 20); // Example of constexpr function usage
    return {sum, multiply(static_cast<T>(5), static_cast<U>(6))}; // Example of lambda usage within template
}

int main() {
    using namespace std;
    vector<vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int result = 0;

    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                auto [sum, product] = calculateSumAndProduct(val, static_cast<double>(1)); // Example of template instantiation within lambda
                result += static_cast<int>(product);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl; // Example of deterministic output
}