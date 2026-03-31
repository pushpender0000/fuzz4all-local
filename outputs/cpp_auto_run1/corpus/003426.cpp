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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(multiply(val, sum));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        } else {
            std::cout << "Error: Vector elements are not of type double." << std::endl;
            return 1;
        }
    }

    constexpr int c = 3;
    consteval auto multiplyConstEval(int a, int b) -> int {
        return a * b + c;
    }

    result += multiplyConstEval(sum, sum);

    std::cout << result << std::endl;
}