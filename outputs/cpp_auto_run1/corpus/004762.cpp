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
void nestedTemplateInstantiation() {
    std::vector<std::vector<U>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    T result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<T>(multiply(val, add(static_cast<U>(1), static_cast<U>(2))));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
            }
        }
    }
    std::cout << result << std::endl;
}

template<typename T>
void lambdaTemplate() {
    auto multiplyLambda = [](T a, T b) -> T {
        return a * b;
    };

    std::vector<T> vec = {1, 2, 3};
    T result = 0;
    for (auto val : vec) {
        result += multiplyLambda(val, add(static_cast<T>(1), static_cast<T>(2)));
    }
    std::cout << result << std::endl;
}

int main() {
    nestedTemplateInstantiation<double, int>();
    lambdaTemplate<int>();
}