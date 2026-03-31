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
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec, U multiplier) {
    using ResultType = decltype(vec[0][0] * multiplier);
    ResultType total = 0;
    for (const auto& subVec : vec) {
        for (auto val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                total += val * multiplier;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return static_cast<ResultType>(-1); // Indicate error with a negative result
            }
        }
    }
    return total;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    constexpr double multiplier = 2.5;
    auto finalResult = multiplyAndAdd(nestedVector, multiplier);
    if (finalResult >= 0) {
        std::cout << static_cast<int>(finalResult) << std::endl; // Ensure output is an integer
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}