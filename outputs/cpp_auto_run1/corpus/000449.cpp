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

template<typename T>
auto sumVector(const std::vector<std::vector<T>>& vecVec) {
    T result = 0;
    for (const auto& vec : vecVec) {
        for (const auto& val : vec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                result += val;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    constexpr double c = 3.14;
    constexpr double d = 2.71;

    auto sum_ints = add(a, b);
    auto sum_doubles = add(c, d);

    std::vector<std::vector<int>> nestedVectorInt = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> nestedVectorDouble = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};

    int result_ints = sumVector(nestedVectorInt);
    double result_doubles = sumVector(nestedVectorDouble);

    std::cout << (result_ints + static_cast<int>(result_doubles)) << std::endl;
}