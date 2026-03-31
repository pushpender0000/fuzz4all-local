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

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += val * sum;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    constexpr auto multiply = [](int x, int y) {
        if constexpr(std::is_same_v<int, decltype(x)> && std::is_same_v<int, decltype(y)>) {
            return x * y;
        } else {
            throw std::runtime_error("Type mismatch in lambda.");
        }
    };

    try {
        result = multiply(sum, nestedVector.size());
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << result << std::endl;
}