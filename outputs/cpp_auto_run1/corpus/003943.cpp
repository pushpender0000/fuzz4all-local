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
constexpr auto sum_of_products(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic");
    T result = 0;
    for (size_t i = 0; i < vec1.size() && i < vec2.size(); ++i) {
        if constexpr(IsSame<T, U>::value) {
            result += multiply(vec1[i], vec2[i]);
        } else {
            std::cout << "Error: Type mismatch in vector elements." << std::endl;
            std::exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int a = 5, b = 7;
    auto sum_constexpr = add(a, b);

    std::vector<double> vec1 = {1.1, 2.2, 3.3};
    std::vector<int> vec2 = {4, 5, 6};

    constexpr int result = sum_of_products(vec1, vec2);
    std::cout << result << std::endl;
}