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
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            for (int val : vec) {
                result += val * sum;
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    constexpr int x = 3, y = 4;
    auto mul = [](int a, int b) -> int {
        if constexpr(IsSame<decltype(a), int>::value && IsSame<decltype(b), int>::value) {
            return a * b;
        } else {
            std::cout << "Error: Incorrect type used in lambda." << std::endl;
            return 0;
        }
    };

    result = mul(x, y);

    std::cout << result << std::endl;
}