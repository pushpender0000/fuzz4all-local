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
void processVector(const std::vector<std::vector<T>>& vecVec) {
    int result = 0;
    for (const auto& vec : vecVec) {
        if constexpr(!vec.empty() && IsSame<decltype(vec[0]), double>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, add(1.5, 2.5)));
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
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<int>(b));

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    processVector(nestedVector);
}