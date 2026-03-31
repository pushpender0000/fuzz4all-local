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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            result += static_cast<int>(multiply(val, 2));
        }
    }
    return result;
}

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {1.1, 2.2, 3.3};

    auto lambdaSumVec = [](const std::vector<int>& v) -> int {
        return sumVector(v);
    };

    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sumConstexpr = add(a, static_cast<int>(b));

    std::vector<std::vector<double>> nestedVec = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    int resultNested = sumVector(nestedVec[0]);

    for (const auto& vec : nestedVec) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            resultNested += static_cast<int>(sumVector(vec));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << resultNested << std::endl;
}