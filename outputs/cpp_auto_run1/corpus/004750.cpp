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

template<typename T, typename U>
void complexTemplateUsage() {
    constexpr auto multiply_constexpr = [](auto a, auto b) { return a * b; };
    using IntVector = std::vector<T>;
    using DoubleVector = std::vector<U>;

    IntVector intVec{{1}, {2}, {3}};
    DoubleVector doubleVec{{4.4}, {5.5}, {6.6}};

    T sum_int = 0;
    U sum_double = 0.0;

    for (const auto& val : intVec) {
        if constexpr(std::is_integral_v<T>) {
            sum_int += static_cast<T>(add(val, T{1}));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
        }
    }

    for (const auto& val : doubleVec) {
        if constexpr(std::is_floating_point_v<U>) {
            sum_double += add(val, U{1.0});
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
        }
    }

    if constexpr(std::is_integral_v<T> && std::is_floating_point_v<U>) {
        T final_result = static_cast<T>(multiply_constexpr(sum_int, sum_double));
        std::cout << final_result << std::endl;
    } else {
        std::cout << "Error: Type mismatch in complexTemplateUsage." << std::endl;
    }
}

int main() {
    nestedTemplateInstantiation<int, double>();
    complexTemplateUsage<int, double>();
}