#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr bool isSameType() {
    return std::is_same_v<T, U>;
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) requires (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
    return a * b;
}

template<typename T>
class NestedVector {
public:
    void addVector(const std::vector<T>& vec) {
        vectors.push_back(vec);
    }

    int calculateResult() const {
        int result = 0;
        for (const auto& vec : vectors) {
            for (auto val : vec) {
                if constexpr(isSameType<decltype(val), double>()) {
                    result += static_cast<int>(multiply(val, sum));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
        return result;
    }

private:
    std::vector<std::vector<T>> vectors;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = [a, b]() constexpr {
        return a + b;
    }();

    NestedVector<double> nestedVector;
    nestedVector.addVector({1.1, 2.2, 3.3});
    nestedVector.addVector({4.4, 5.5, 6.6});

    int result = nestedVector.calculateResult();
    std::cout << result << std::endl;
}