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
auto multiplyVectorElements(const std::vector<T>& vec1, const std::vector<U>& vec2) -> int {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic.");
    int result = 0;
    for (const auto& elem1 : vec1) {
        if constexpr(IsSame<decltype(elem1), T>::value) {
            for (const auto& elem2 : vec2) {
                if constexpr(IsSame<decltype(elem2), U>::value) {
                    result += static_cast<int>(elem1 * elem2);
                }
            }
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector1 = {{1.0, 2.0}, {3.0, 4.0}};
    std::vector<std::vector<double>> nestedVector2 = {{5.0, 6.0}, {7.0, 8.0}};

    int result = multiplyVectorElements(nestedVector1[0], nestedVector2[1]);

    std::cout << result << std::endl;
}