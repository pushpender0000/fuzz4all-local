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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    auto multiplyAndAdd = [](const std::vector<std::vector<double>>& vec, double multiplier) {
        double total = 0;
        for (const auto& subVec : vec) {
            for (double val : subVec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    total += val * multiplier;
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return -1.0 / 0.0; // Indicate error with a NaN result
                }
            }
        }
        return total;
    };

    constexpr double multiplier = 2.5;
    auto finalResult = multiplyAndAdd(nestedVector, multiplier);
    if (std::isfinite(finalResult)) {
        std::cout << static_cast<int>(finalResult) << std::endl; // Ensure output is an integer
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}