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
constexpr auto sum_vector(const std::vector<T>& vec, const std::vector<U>& vec2) -> T {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic.");
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
            result += multiply(val, static_cast<T>(*vec2.data()));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(std::is_arithmetic_v<int>) {
            result += sum_vector(vec, vec);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}