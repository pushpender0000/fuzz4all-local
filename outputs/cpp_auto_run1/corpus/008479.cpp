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
constexpr auto divide(T a, U b) -> std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, decltype(a / b)> {
    return a / b;
}

template<typename T>
constexpr auto square(T x) -> decltype(x * x) {
    return x * x;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<double, double>::value) {
            result += static_cast<int>(multiply(vec[1], sum));
            result -= static_cast<int>(divide(vec[2], 2.0));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<int>> intNestedVector;
    intNestedVector.push_back({1, 2, 3});
    intNestedVector.push_back({4, 5, 6});

    for (const auto& vec : intNestedVector) {
        if constexpr(IsSame<int, int>::value) {
            result += multiply(vec[1], sum);
            result -= divide(vec[2], 2);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<int> numbers = {10, 20, 30};
    auto lambdaSum = [](const std::vector<int>& vec) -> int {
        int sum = 0;
        for (int num : vec) {
            sum += num;
        }
        return sum;
    };

    result += lambdaSum(numbers);

    std::cout << "Result: " << result << std::endl;
}