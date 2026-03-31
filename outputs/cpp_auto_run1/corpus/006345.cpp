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

template<typename T, typename U, typename V>
auto nestedMultiply(const std::vector<std::vector<T>>& vecVec, const std::vector<U>& vec, V scalar) -> V {
    static_assert(IsSame<V, double>::value || IsSame<V, int>::value, "Scalar type must be either double or int.");
    V result = 0;
    for (const auto& row : vecVec) {
        for (auto val : row) {
            if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(scalar), V>::value) {
                result += static_cast<V>(multiply(val, scalar));
            } else {
                std::cout << "Error: Incorrect types used in calculation." << std::endl;
                return 1;
            }
        }
    }
    for (auto elem : vec) {
        if constexpr(IsSame<decltype(elem), U>::value && IsSame<decltype(scalar), V>::value) {
            result += static_cast<V>(multiply(elem, scalar));
        } else {
            std::cout << "Error: Incorrect types used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, a);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> vec = {7, 8, 9};
    int scalar = 2;

    auto result = nestedMultiply(nestedVector, vec, scalar);

    std::cout << result << std::endl;
}