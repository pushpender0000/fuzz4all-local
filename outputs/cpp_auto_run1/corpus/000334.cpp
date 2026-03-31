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

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            for (int val : vec) {
                result += multiply(val, sum);
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<double>> nestedVectorDouble;
    nestedVectorDouble.push_back({1.1, 2.2, 3.3});
    nestedVectorDouble.push_back({4.4, 5.5, 6.6});

    double resultDouble = 0;
    for (const auto& vec : nestedVectorDouble) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            for (double val : vec) {
                resultDouble += multiply(val, sum);
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<int>> nestedVectorLarge;
    for (int i = 0; i < 100; ++i) {
        nestedVectorLarge.push_back({i, i+1, i+2});
    }

    int resultLarge = 0;
    for (const auto& vec : nestedVectorLarge) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            for (int val : vec) {
                resultLarge += multiply(val, sum);
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result + resultDouble + resultLarge << std::endl;
}