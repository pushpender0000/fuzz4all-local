#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename U>
constexpr auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<double>(b));

    std::vector<std::vector<float>> nestedVector;
    nestedVector.push_back({1.1f, 2.2f, 3.3f});
    nestedVector.push_back({4.4f, 5.5f, 6.6f});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<float, float>::value) {
            result += static_cast<int>(multiply(vec[1], sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}