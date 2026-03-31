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
constexpr auto calculateSum(const std::vector<std::vector<T>>& nestedVector) -> int {
    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), T>::value && std::is_arithmetic_v<T>) {
                result += static_cast<int>(multiply(val, add(val, 1)));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1;
            }
        }
    }
    return result;
}

int main() {
    constexpr int size = 3;
    std::vector<std::vector<double>> nestedVector(size, std::vector<double>(size, 0.0));
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            nestedVector[i][j] = static_cast<double>(i * size + j + 1);
        }
    }

    int result = calculateSum(nestedVector);
    std::cout << result << std::endl;
}