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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    constexpr double c = 3.14;
    constexpr double d = 2.71;
    auto sumInt = add(a, b);
    auto sumDouble = add(c, d);

    std::vector<std::vector<int>> nestedVectorInt;
    nestedVectorInt.push_back({1, 2, 3});
    nestedVectorInt.push_back({4, 5, 6});

    std::vector<std::vector<double>> nestedVectorDouble;
    nestedVectorDouble.push_back({1.1, 2.2, 3.3});
    nestedVectorDouble.push_back({4.4, 5.5, 6.6});

    int resultInt = 0;
    for (const auto& vec : nestedVectorInt) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                resultInt += val * sumInt;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    double resultDouble = 0.0;
    for (const auto& vec : nestedVectorDouble) {
        for (double val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                resultDouble += val * sumDouble;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << static_cast<int>(resultInt + resultDouble) << std::endl;
}