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
void printSum(const std::vector<std::vector<T>>& vecVec) {
    int result = 0;
    for (const auto& vec : vecVec) {
        if constexpr(IsSame<T, double>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, add(static_cast<double>(1), static_cast<double>(2))));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int size = 5;
    std::vector<std::vector<double>> nestedVector(size, std::vector<double>(size, static_cast<double>(3)));
    printSum(nestedVector);
}