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
constexpr auto fibonacci(int n) -> std::enable_if_t<std::is_integral_v<T>, T> {
    if (n <= 1) return static_cast<T>(n);
    T a = 0, b = 1;
    for (int i = 2; i < n; ++i) {
        T temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

template<typename T>
auto generateVector(int size, T value) -> std::vector<T> {
    std::vector<T> vec(size);
    for (auto& v : vec) v = value;
    return vec;
}

int main() {
    constexpr int a = 5;
    constexpr int b = fibonacci<long long>(10);
    auto sum = add(a, static_cast<decltype(a)>(b));

    std::vector<std::vector<double>> nestedVector;
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