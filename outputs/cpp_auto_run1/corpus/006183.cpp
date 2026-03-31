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
void processVector(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    if constexpr (IsSame<T, double>::value && IsSame<U, int>::value) {
        for (size_t i = 0; i < vec1.size() && i < vec2.size(); ++i) {
            auto result = multiply(vec1[i], vec2[i]);
            std::cout << static_cast<int>(result) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: Incorrect type combination." << std::endl;
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<int>(b));

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2}, {3.3, 4.4}};
    std::vector<std::vector<int>> nestedVector2 = {{5, 6}, {7, 8}};

    processVector(nestedVector1[0], nestedVector2[0]);
}