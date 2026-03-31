#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
class NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = [a, b]() consteval { return a + static_cast<int>(b); }();

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}