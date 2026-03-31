#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr bool isSameType() {
    return std::is_same_v<T, U>;
}

template<typename T>
constexpr auto add(T a, T b) -> T {
    static_assert(std::numeric_limits<T>::is_integer || std::numeric_limits<T>::is_floating_point, "Type must be numeric");
    return a + b;
}

template<typename T>
constexpr auto multiply(T a, T b) -> decltype(a * b) {
    static_assert(std::numeric_limits<T>::is_arithmetic, "Type must be arithmetic");
    return a * b;
}

template<typename T>
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(isSameType<decltype(val), double>()) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}