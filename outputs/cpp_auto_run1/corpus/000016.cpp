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
    std::vector<typename std::common_type<T, U>::type> result;
    for (const auto& val1 : vec1) {
        for (const auto& val2 : vec2) {
            if constexpr(IsSame<decltype(val1 * val2), double>::value) {
                result.push_back(val1 * val2);
            } else {
                std::cout << "Error: Incorrect type used in multiplication." << std::endl;
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

    std::vector<std::vector<double>> nestedVector1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    std::vector<std::vector<int>> nestedVector2 = {{1, 2, 3}, {4, 5, 6}};

    auto resultVector = multiplyVectors(nestedVector1[0], nestedVector2[1]);

    int result = 0;
    for (const auto& val : resultVector) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(val * sum);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}