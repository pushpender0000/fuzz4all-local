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
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    double result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            std::vector<double> tempVec = vec;
            for (auto val : tempVec) {
                if constexpr(IsSame<decltype(val), double>::value) {
                    result += static_cast<int>(val * sum);
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        } else {
            std::cout << "Error: Incorrect type used in vector declaration." << std::endl;
            return 1;
        }
    }

    std::cout << (int)result << std::endl;
}