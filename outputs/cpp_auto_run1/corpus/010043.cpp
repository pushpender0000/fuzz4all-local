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
constexpr auto sum_vector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            throw std::invalid_argument("Error: Incorrect type used in calculation.");
        }
    }
    return result;
}

template<typename T, typename U>
constexpr auto compute(const std::vector<T>& vec1, const std::vector<U>& vec2) -> int {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Error: Vectors must be of the same size.");
    }
    T sum = 0;
    for (std::size_t i = 0; i < vec1.size(); ++i) {
        if constexpr(IsSame<decltype(vec1[i]), int>::value && IsSame<decltype(vec2[i]), double>::value) {
            sum += multiply(static_cast<int>(vec1[i]), static_cast<double>(vec2[i]));
        } else {
            throw std::invalid_argument("Error: Incorrect type used in calculation.");
        }
    }
    return static_cast<int>(sum);
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, a);

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {7.0, 8.0, 9.0};

    try {
        int result = compute(vec1, vec2);
        std::cout << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}