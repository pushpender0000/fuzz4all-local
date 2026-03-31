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

    std::vector<std::pair<int, int>> pairs;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec.front()), int>::value) {
            pairs.emplace_back(vec.front(), sum);
        } else {
            std::cout << "Error: Incorrect type used in pair creation." << std::endl;
            return 1;
        }
    }

    for (const auto& p : pairs) {
        result += p.first * p.second;
    }

    std::cout << result << std::endl;
}