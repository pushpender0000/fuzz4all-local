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

template<typename T>
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec, T multiplier) {
    T total = 0;
    for (const auto& subVec : vec) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                total += val * multiplier;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return total;
}

int main() {
    constexpr int multiplier = 2;
    std::vector<std::vector<int>> nestedVector = {{1, 2, 3}, {4, 5, 6}};
    
    auto result = multiplyAndAdd(nestedVector, multiplier);
    if (result >= 0) {
        std::cout << "Total: " << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}