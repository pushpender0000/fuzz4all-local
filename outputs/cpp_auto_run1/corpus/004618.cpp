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
void nestedMultiplyAndAdd(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2) {
    static_assert(!vec1.empty() && !vec2.empty(), "Vectors must not be empty");

    T sum = 0;
    for (const auto& row : vec1) {
        if constexpr(IsSame<T, double>::value) {
            U mulResult = multiply(row[0], row[1]);
            sum += static_cast<T>(mulResult);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    std::cout << add(sum, vec2[0]) << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2}, {3.3, 4.4}};
    std::vector<int> vec2 = {5};

    nestedMultiplyAndAdd(nestedVector, vec2);
}