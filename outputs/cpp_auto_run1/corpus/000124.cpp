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
    for (size_t i = 0; i < vec1.size() && i < vec2.size(); ++i) {
        result.push_back(add(vec1[i], vec2[i]));
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> nestedVector2 = {{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}};

    auto resultVector = multiplyVectors(nestedVector1, nestedVector2);

    int finalResult = 0;
    for (const auto& vec : resultVector) {
        for (const auto& val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                finalResult += static_cast<int>(val * sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << finalResult << std::endl;
}