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
auto multiplyVectors(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic");
    std::vector<decltype(add(T(), U()))> result;
    for (const auto& val1 : vec1) {
        for (const auto& val2 : vec2) {
            if constexpr(IsSame<decltype(val1), decltype(val2)>::value && IsSame<decltype(val1), int>::value) {
                result.push_back(val1 * val2);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> nestedVector2 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    auto resultVec = multiplyVectors(nestedVector1[0], nestedVector2[1]);

    int finalResult = 0;
    for (const auto& val : resultVec) {
        finalResult += static_cast<int>(val);
    }

    std::cout << finalResult << std::endl;
}