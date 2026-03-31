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

template<typename T, typename U, typename V>
constexpr auto complexOperation(T a, U b, V c) -> std::enable_if_t<!std::is_same_v<T, double>, int> {
    if constexpr (IsSame<U, double>::value) {
        return static_cast<int>(multiply(add(a, b), c));
    } else {
        return static_cast<int>(add(a, b) * c);
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    constexpr double c = 3.14;

    auto result = complexOperation(a, b, c);
    std::cout << result << std::endl;
}