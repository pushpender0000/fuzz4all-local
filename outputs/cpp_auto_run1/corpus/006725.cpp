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

template<typename T, size_t N>
constexpr auto sumArray(const std::vector<T>& vec) -> T {
    T result = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if constexpr(IsSame<decltype(vec[i]), double>::value) {
            result += static_cast<int>(multiply(vec[i], N));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T>
struct Summation {
    T value;
};

template<typename T, size_t N>
constexpr auto sumNestedVectors(const std::vector<std::vector<T>>& nestedVec) -> Summation<int> {
    int result = 0;
    for (const auto& vec : nestedVec) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            result += sumArray<double, N>(vec);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return Summation<int>{1};
        }
    }
    return Summation<int>{result};
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    constexpr size_t multiplier = 2;

    auto finalResult = sumNestedVectors<double, multiplier>(nestedVector);
    std::cout << finalResult.value << std::endl;
}