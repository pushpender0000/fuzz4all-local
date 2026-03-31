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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(nestedVector.size() > 1) { // Ensure we have at least two vectors to trigger the condition
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(multiply(val, sum));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        } else {
            std::cout << "Only one vector present. No multiplication performed." << std::endl;
        }
    }

    if constexpr(result != 0) { // Ensure the result is non-zero to trigger this condition
        std::cout << result << std::endl;
    } else {
        std::cout << "Result is zero due to incorrect type usage." << std::endl;
    }
}