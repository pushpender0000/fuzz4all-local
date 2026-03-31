#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename... Args>
constexpr auto sum(Args&&... args) -> T {
    return (args + ...);
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto totalSum = sum<decltype(a + b)>(a, b);

    std::vector<std::vector<int>> nestedVector(3, std::vector<int>(3));
    for (auto& row : nestedVector) {
        for (auto& val : row) {
            val = totalSum;
        }
    }

    int result = 0;
    auto lambdaMultiply = [](int x, int y) { return multiply(x, y); };

    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += lambdaMultiply(val, totalSum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}