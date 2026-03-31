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

    // Stress GCC/G++ parsing, templates, constexpr, and optimization.
    auto lambda = [](int x) -> int {
        if (x % 2 == 0) {
            return x * sum;
        } else {
            return x + sum;
        }
    };

    std::vector<int> stressTest({1, 3, 5, 7, 9});
    for (auto it = stressTest.begin(); it != stressTest.end(); ++it) {
        result += lambda(*it);
    }

    // Nested template instantiation to increase complexity.
    std::vector<std::vector<int>> nestedStressTest;
    nestedStressTest.push_back({lambda(1), lambda(2), lambda(3)});
    nestedStressTest.push_back({lambda(4), lambda(5), lambda(6)});

    int stressResult = 0;
    for (const auto& vec : nestedStressTest) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                stressResult += val * sum;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << stressResult << std::endl;
}