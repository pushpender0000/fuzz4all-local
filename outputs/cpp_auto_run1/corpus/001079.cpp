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
    std::vector<std::vector<T>> data;

    constexpr auto sumNestedVector() const {
        T result = 0;
        for (const auto& vec : data) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += multiply(val, static_cast<T>(1)); // Simplified multiplication for demonstration
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    throw 1;
                }
            }
        }
        return result;
    }
};

template<typename T>
class LambdaClass {
public:
    void lambdaTest(T val) const {
        auto lambda = [this, val]() -> T {
            if constexpr (std::is_arithmetic_v<T>) {
                return add(val, static_cast<T>(1));
            } else {
                std::cout << "Error: Non-arithmetic type used in lambda." << std::endl;
                throw 2;
            }
        };

        T result = lambda();
        std::cout << result << std::endl;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.data = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    try {
        int result = nestedVector.sumNestedVector();
        std::cout << result << std::endl;
    } catch (int e) {
        return e;
    }

    LambdaClass<double> lc;
    lc.lambdaTest(3.0);
}