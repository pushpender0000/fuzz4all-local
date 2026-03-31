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
auto multiplyAndAdd(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2) {
    int total = 0;
    for (const auto& subVec : vec1) {
        for (const auto& val : subVec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                total += static_cast<int>(val * vec2[subVec.size()]);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Indicate error with a negative result
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

    std::vector<int> intVec = {10, 20, 30};

    auto result = multiplyAndAdd(nestedVector, intVec);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Calculation failed." << std::endl;
    }
}