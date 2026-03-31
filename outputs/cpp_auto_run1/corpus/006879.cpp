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
void nestedMultiplyAdd(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2, V& result) {
    for (const auto& row : vec1) {
        if constexpr(IsSame<decltype(row[0]), T>::value && IsSame<decltype(*vec2.begin()), U>::value) {
            for (auto val : row) {
                *result = add(*result, multiply(val, static_cast<V>(*vec2.begin())));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    nestedMultiplyAdd(nestedVector, std::vector<int>{7}, result);

    std::cout << result << std::endl;
}