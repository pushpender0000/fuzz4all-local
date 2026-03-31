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
            result += static_cast<int>(multiply(val, N));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T>
constexpr auto average(const std::vector<T>& vec) -> double {
    if (vec.empty()) return 0.0;
    constexpr T zero = 0;
    T sum = zero;
    for (const auto& val : vec) {
        sum += val;
    }
    return static_cast<double>(sum) / vec.size();
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    constexpr std::size_t n = 2;
    auto totalSum = sumVector<double, n>(nestedVector[0]);

    std::cout << totalSum << std::endl;

    std::vector<int> nums{10, 20, 30, 40, 50};
    auto avg = average(nums);
    std::cout << avg << std::endl;
}