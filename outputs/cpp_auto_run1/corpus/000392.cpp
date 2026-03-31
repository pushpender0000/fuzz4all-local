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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    constexpr double c = 3.14;
    constexpr double d = 2.71;

    auto sum_ints = add(a, b);
    auto sum_doubles = add(c, d);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result_ints = 0;
    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result_ints += val * sum_ints;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::vector<std::vector<double>> nestedVectorDouble;
    nestedVectorDouble.push_back({1.1, 2.2, 3.3});
    nestedVectorDouble.push_back({4.4, 5.5, 6.6});

    double result_doubles = 0;
    for (const auto& vec : nestedVectorDouble) {
        for (double val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result_doubles += val * sum_doubles;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    constexpr auto multiply = [](auto a, auto b) {
        if constexpr(std::is_arithmetic_v<decltype(a)> && std::is_arithmetic_v<decltype(b)>) {
            return a * b;
        } else {
            throw std::invalid_argument("Arguments must be arithmetic types.");
        }
    };

    int finalResult = 0;
    try {
        finalResult = multiply(result_ints, static_cast<int>(result_doubles));
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << finalResult << std::endl;
}