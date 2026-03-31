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
    if (vec.empty()) {
        std::cout << "Error: Vector is empty." << std::endl;
        return;
    }
    T sum = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            sum += add(val, val);
        } else if constexpr(IsSame<decltype(val), double>::value) {
            sum += static_cast<int>(multiply(val, 2.0));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << sum << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(add(a, a))>(b));

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    processVector(nestedVector[0]);
}