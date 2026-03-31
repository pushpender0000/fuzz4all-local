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

template<typename T, typename U>
auto computeNestedVector(const std::vector<T>& vec1, const std::vector<U>& vec2) -> int {
    if constexpr (IsSame<T, double>::value && IsSame<U, double>::value) {
        int result = 0;
        for (size_t i = 0; i < vec1.size(); ++i) {
            result += static_cast<int>(multiply(vec1[i], vec2[i]));
            result -= static_cast<int>(divide(vec1[i], vec2[i]));
        }
        return result;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
        return -1;
    }
}

template<typename T>
auto generateVector(size_t size) -> std::vector<T> {
    std::vector<T> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = static_cast<T>(i + 1);
    }
    return vec;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    auto vecA = generateVector<double>(3);
    auto vecB = generateVector<double>(3);

    int result = computeNestedVector(vecA, vecB);
    std::cout << result << std::endl;
}