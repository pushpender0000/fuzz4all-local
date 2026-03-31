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

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (double val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(val * sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    auto multiplyAndAdd = [](const std::vector<std::vector<double>>& vec, int multiplier) {
        int total = 0;
        for (const auto& subVec : vec) {
            for (double val : subVec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    total += static_cast<int>(val * multiplier);
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return -1; // Indicate error with a negative result
                }
            }
        }
        return total;
    };

    constexpr int multiplier = 2;
    auto finalResult = multiplyAndAdd(nestedVector, multiplier);
    if (finalResult >= 0) {
        std::cout << finalResult << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}