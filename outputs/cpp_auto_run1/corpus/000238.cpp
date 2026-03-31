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

template<typename T>
auto multiplyVector(const std::vector<T>& vec) -> T {
    T result = 1;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result *= val;
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
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

    int finalResult = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec), std::vector<int>>::value) {
            finalResult += multiplyVector(vec);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << finalResult << std::endl;
}