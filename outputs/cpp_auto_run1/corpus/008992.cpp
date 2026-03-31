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
constexpr auto divide(T a, U b) -> std::enable_if_t<std::is_arithmetic_v<U>, double> {
    if (b != 0) {
        return static_cast<double>(a) / b;
    } else {
        throw std::runtime_error("Division by zero");
    }
}

template<typename T, typename U>
void nestedTemplate(T a, U b) {
    if constexpr(IsSame<decltype(a), int>::value && IsSame<decltype(b), double>::value) {
        try {
            auto result = add(a, static_cast<decltype(a)>(b));
            std::cout << multiply(result, 2.5f) << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        throw std::invalid_argument("Incorrect types used in nested template instantiation");
    }
}

template<typename T, typename U>
auto lambdaMultiply(T a, U b) -> decltype(a * b) {
    auto mul = [](auto x, auto y) { return x * y; };
    return mul(a, b);
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    nestedTemplate(a, b);

    std::vector<int> vec{1, 2, 3};
    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it % 2 == 0) {
            it = vec.erase(it);
        } else {
            ++it;
        }
    }

    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}