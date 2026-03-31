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
    if constexpr(IsSame<T, double>::value && IsSame<U, int>::value) {
        for (size_t i = 0; i < vec1.size(); ++i) {
            auto result = multiply(vec1[i], static_cast<int>(vec2[i]));
            std::cout << result << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(a)>(b));

    std::vector<double> vec1 = {1.1, 2.2, 3.3};
    std::vector<int> vec2 = {4, 5, 6};

    processVector(vec1, vec2);
}