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
class NestedTemplate {
public:
    NestedTemplate(const std::vector<T>& vec1, const std::vector<U>& vec2) : vector1(vec1), vector2(vec2) {}

    auto calculate() -> int {
        static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, "Types must be arithmetic");
        return sumVectors();
    }

private:
    const std::vector<T>& vector1;
    const std::vector<U>& vector2;

    auto sumVectors() -> int {
        static_assert(IsSame<T, double>::value && IsSame<U, double>::value, "All types must be double");
        int result = 0;
        for (size_t i = 0; i < vector1.size(); ++i) {
            if constexpr(IsSame<double, double>::value) {
                result += static_cast<int>(multiply(vector1[i], vector2[i]));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        return result;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    NestedTemplate<double, double> nt(nestedVector[0], nestedVector[1]);
    int result = nt.calculate();

    std::cout << result << std::endl;
}