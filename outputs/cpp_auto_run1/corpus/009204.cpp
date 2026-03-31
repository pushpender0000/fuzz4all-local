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
struct NestedTemplate {
    std::vector<std::vector<T>> nestedVector;

    void addRow(const std::vector<T>& row) {
        nestedVector.push_back(row);
    }

    auto calculateResult() const {
        int result = 0;
        for (const auto& vec : nestedVector) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += static_cast<int>(multiply(val, add(T{1}, T{2})));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    std::exit(1);
                }
            }
        }
        return result;
    }
};

template<typename T, typename U>
constexpr auto computeLambda(T a, U b) {
    auto lambda = [a, b]() constexpr {
        if constexpr(IsSame<decltype(a), decltype(b)>::value && std::is_arithmetic_v<decltype(a)>) {
            return multiply(add(a, b), T{3});
        } else {
            throw std::runtime_error("Type mismatch or non-arithmetic type.");
        }
    };
    return lambda();
}

int main() {
    NestedTemplate<double> nestedDouble;
    nestedDouble.addRow({1.1, 2.2, 3.3});
    nestedDouble.addRow({4.4, 5.5, 6.6});

    std::cout << nestedDouble.calculateResult() << std::endl;

    try {
        auto result = computeLambda(10, 20); // Example usage of lambda with constexpr and arithmetic types
        std::cout << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}