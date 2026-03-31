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

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), double>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<int>> nestedIntVector;
    nestedIntVector.push_back({1, 2, 3});
    nestedIntVector.push_back({4, 5, 6});

    for (const auto& vec : nestedIntVector) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<float>> nestedFloatVector;
    nestedFloatVector.push_back({1.2f, 2.3f, 3.4f});
    nestedFloatVector.push_back({4.5f, 5.6f, 6.7f});

    for (const auto& vec : nestedFloatVector) {
        if constexpr(IsSame<decltype(vec[0]), float>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::vector<std::vector<long>> nestedLongVector;
    nestedLongVector.push_back({10L, 20L, 30L});
    nestedLongVector.push_back({40L, 50L, 60L});

    for (const auto& vec : nestedLongVector) {
        if constexpr(IsSame<decltype(vec[0]), long>::value) {
            for (auto val : vec) {
                result += static_cast<int>(multiply(val, sum));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}