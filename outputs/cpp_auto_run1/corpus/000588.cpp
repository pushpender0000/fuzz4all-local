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
void processVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            std::cout << multiply(val, 2);
        } else {
            std::cout << "Error: Incorrect type used in calculation.";
            exit(1);
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    processVector(nestedVector[0]);
}