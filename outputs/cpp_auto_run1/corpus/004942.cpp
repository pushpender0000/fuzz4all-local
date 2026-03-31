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

template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            std::cout << multiply(val, 2) << " ";
        } else if constexpr(IsSame<decltype(val), double>::value) {
            std::cout << multiply(val, 1.5) << " ";
        } else {
            std::cout << "Error: Unsupported type." << std::endl;
            exit(1);
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(sum)>(b));

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        printVector(vec);
    }

    std::cout << std::endl;
}