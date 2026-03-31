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
void nestedTemplate(const std::vector<std::vector<U>>& data, const T& scalar) {
    if constexpr (IsSame<T, double>::value) {
        int result = 0;
        for (const auto& vec : data) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, scalar));
            }
        }
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.1;
    auto sum = add(a, static_cast<decltype(a)>(b));

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    nestedTemplate(nestedVector, sum);
}