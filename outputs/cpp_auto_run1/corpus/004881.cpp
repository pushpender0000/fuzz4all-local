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
void complexCalculation() {
    std::vector<T> vec;
    for (int i = 0; i < 10; ++i) {
        if constexpr(std::is_integral_v<T>) {
            vec.push_back(static_cast<T>(i * i));
        } else if constexpr(std::is_floating_point_v<T>) {
            vec.push_back(static_cast<T>(i) / 3.14);
        }
    }

    T sum = 0;
    for (auto val : vec) {
        if constexpr(std::is_arithmetic_v<T>) {
            sum += val;
        } else {
            std::cout << "Error: Unsupported type in arithmetic operations." << std::endl;
        }
    }

    U factor = 2.5;
    auto mulLambda = [factor](auto x) -> decltype(x * factor) {
        return x * factor;
    };

    T finalResult = sum;
    for (auto val : vec) {
        if constexpr(std::is_arithmetic_v<T>) {
            finalResult += mulLambda(val);
        } else {
            std::cout << "Error: Unsupported type in lambda operation." << std::endl;
        }
    }

    std::cout << finalResult << std::endl;
}

int main() {
    complexCalculation<double, float>();
}