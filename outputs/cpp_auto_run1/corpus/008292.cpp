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
void processNestedVector(const std::vector<std::vector<T>>& nestedVec, const U& scalar) {
    int result = 0;
    for (const auto& vec : nestedVec) {
        if constexpr(IsSame<decltype(vec[0]), T>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, scalar));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    constexpr double scalar = 2.0;
    processNestedVector(nestedVector, scalar);
}