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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            result += static_cast<int>(multiply(val, 2));
        }
    }
    return result;
}

int main() {
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    auto totalSum = sumVector(nestedVector[0]);
    totalSum += sumVector(nestedVector[1]);

    std::cout << static_cast<int>(totalSum) << std::endl;
}