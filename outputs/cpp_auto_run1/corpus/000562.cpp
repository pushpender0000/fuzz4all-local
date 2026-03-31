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
void nestedMultiplyAdd(const std::vector<std::vector<T>>& vecVec, const std::vector<U>& vec) {
    int result = 0;
    for (const auto& innerVec : vecVec) {
        if constexpr(!innerVec.empty() && IsSame<decltype(innerVec[0]), T>::value) {
            for (const auto& val : innerVec) {
                if constexpr(IsSame<decltype(val), T>::value && !vec.empty()) {
                    result += static_cast<int>(multiply(val, vec[0]));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return;
                }
            }
        } else {
            std::cout << "Error: Incorrect nested vector or element types." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> vec = {10};

    nestedMultiplyAdd(nestedVector, vec);
}