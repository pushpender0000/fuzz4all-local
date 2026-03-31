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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = T{};
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<T>(multiply(val, 2.0));
        } else {
            result += add(val, val);
        }
    }
    return result;
}

int main() {
    constexpr int size = 3;
    std::vector<int> vec1(size, 1);
    std::vector<double> vec2(size, 2.5);

    auto sumInt = [](const std::vector<int>& v) { return sumVector(v); };
    auto sumDouble = [](const std::vector<double>& v) { return sumVector(v); };

    int result1 = sumInt(vec1);
    double result2 = sumDouble(vec2);

    std::cout << (result1 * static_cast<int>(result2)) << std::endl;
}