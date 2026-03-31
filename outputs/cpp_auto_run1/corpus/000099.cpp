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
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec, int multiplier) {
    int total = 0;
    for (const auto& subVec : vec) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                total += static_cast<int>(val * multiplier);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return total;
}

template<typename T, typename U>
auto multiplyAndAdd2(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2) {
    int total = 0;
    for (const auto& subVec : vec1) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value && IsSame<U, double>::value) {
                total += static_cast<int>(val * static_cast<double>(vec2.size()));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
            }
        }
    }
    return total;
}

int main() {
    constexpr int multiplier = 3;
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    
    auto result = multiplyAndAdd(nestedVector, multiplier);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }

    std::vector<double> vec2 = {1.0, 2.0, 3.0};
    auto result2 = multiplyAndAdd2(nestedVector, vec2);
    if (result2 >= 0) {
        std::cout << result2 << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}