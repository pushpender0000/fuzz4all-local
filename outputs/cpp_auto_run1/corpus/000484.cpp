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
        if constexpr(IsSame<decltype(val), T>::value) {
            result += val;
        } else {
            throw std::invalid_argument("Error: Incorrect type used in calculation.");
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    try {
        for (const auto& vec : nestedVector) {
            if constexpr(IsSame<decltype(vec[0]), double>::value) {
                result += static_cast<int>(sumVector<double, vec.size()>(vec));
            } else {
                throw std::invalid_argument("Error: Incorrect type used in calculation.");
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << result << std::endl;
}