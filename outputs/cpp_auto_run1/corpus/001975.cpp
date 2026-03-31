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
struct NestedTemplate {
    std::vector<U> nestedVector;
    NestedTemplate(const std::initializer_list<U>& initList) : nestedVector(initList) {}
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double, double> nestedDouble{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    int result = 0;
    for (const auto& vec : nestedDouble.nestedVector) {
        if constexpr(IsSame<decltype(vec), double>::value) {
            result += static_cast<int>(multiply(vec, sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}