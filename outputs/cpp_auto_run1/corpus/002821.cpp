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
constexpr auto calculateSumVector(const std::vector<T>& vec) -> T {
    T sum = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            sum += static_cast<int>(multiply(val, 2.0));
        } else if constexpr(IsSame<decltype(val), int>::value) {
            sum += add(val, val);
        } else {
            std::cout << "Error: Unsupported type in vector." << std::endl;
            exit(1);
        }
    }
    return sum;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(sum)>(b));

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    auto sumNested1 = calculateSumVector(nestedVector1[0]);

    std::vector<int> intVector = {1, 2, 3, 4, 5};
    auto sumIntVector = calculateSumVector(intVector);

    std::cout << (sum + static_cast<int>(sumNested1) + sumIntVector) << std::endl;
}