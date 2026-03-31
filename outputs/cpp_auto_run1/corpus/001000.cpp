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
}