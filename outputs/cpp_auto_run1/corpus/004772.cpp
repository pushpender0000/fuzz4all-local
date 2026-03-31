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
            result += static_cast<int>(multiply(val, 2));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T>
constexpr auto sum_nested_vector(const std::vector<std::vector<T>>& nestedVec) -> T {
    T totalSum = 0;
    for (const auto& vec : nestedVec) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            totalSum += sum_vector(vec);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return totalSum;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int result = sum_nested_vector(nestedVector);

    std::cout << result << std::endl;
}