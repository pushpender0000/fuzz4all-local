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

template<typename T, typename F>
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec, F multiplier) {
    T total = 0;
    for (const auto& subVec : vec) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                total += val * multiplier;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return static_cast<T>(-1); // Indicate error with a negative result
            }
        }
    }
    return total;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    constexpr int multiplier = 2;
    auto finalResult = multiplyAndAdd(nestedVector, multiplier);
    if (finalResult >= 0) {
        std::cout << finalResult << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}