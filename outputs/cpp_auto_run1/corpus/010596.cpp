#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>

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
struct NestedTemplate : public std::vector<std::vector<T>> {};

template<typename T, size_t N>
consteval auto fibonacci() {
    if constexpr (N == 0) return 0;
    if constexpr (N == 1) return 1;
    return fibonacci<T, N - 1>() + fibonacci<T, N - 2>();
}

int main() {
    constexpr int a = fibonacci<int, 10>();
    constexpr int b = fibonacci<int, 9>();
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({std::sqrt(2), std::sqrt(3), std::sqrt(5)});
    nestedVector.push_back({std::sqrt(7), std::sqrt(11), std::sqrt(13)});

    double result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}