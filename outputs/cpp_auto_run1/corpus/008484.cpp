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
constexpr auto computeNestedSum(const std::vector<std::vector<T>>& vecVec, const U& factor) -> T {
    if constexpr (IsSame<T, double>::value) {
        T sum = 0;
        for (const auto& vec : vecVec) {
            if (!vec.empty()) {
                sum += static_cast<int>(multiply(vec[1], factor));
            } else {
                return 0; // Handle empty vector case gracefully
            }
        }
        return sum;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
        return -1; // Indicate error with a specific value
    }
}

int main() {
    constexpr int factor = 2;
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    
    auto result = computeNestedSum(nestedVector, factor);
    if constexpr (result >= 0) { // Ensure the computation was successful before printing
        std::cout << result << std::endl;
    } else {
        std::cerr << "Error during computation." << std::endl;
    }
}