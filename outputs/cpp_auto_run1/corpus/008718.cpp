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

template<typename T, std::size_t N>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, 2.5));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T, std::size_t N>
constexpr auto generateVector(T value) -> std::vector<T> {
    std::vector<T> vec(N);
    for (std::size_t i = 0; i < N; ++i) {
        vec[i] = value + static_cast<T>(i * 1.5);
    }
    return vec;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, a);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = sumVector<double, 3>(nestedVector[0]);
    std::cout << "Sum of first vector: " << result << std::endl;
}