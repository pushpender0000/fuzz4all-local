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

template<typename T, size_t N>
constexpr auto sumArray(const std::vector<std::vector<T>>& vecVec) -> T {
    static_assert(N > 0, "Array size must be positive");
    T result = 0;
    for (const auto& vec : vecVec) {
        if constexpr(IsSame<decltype(vec[0]), T>::value && vec.size() == N) {
            for (auto val : vec) {
                result += static_cast<T>(multiply(val, add(1, 1))); // Addition should be safe as long as T is arithmetic
            }
        } else {
            std::cout << "Error: Incorrect type or size used in calculation." << std::endl;
            return -1;
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int result = sumArray<double, 3>(nestedVector);

    if constexpr(IsSame<decltype(result), int>::value) {
        std::cout << "Result of multiplication and addition: " << result << std::endl;
    } else {
        std::cout << "Error: Result type is not as expected." << std::endl;
        return 1;
    }
}