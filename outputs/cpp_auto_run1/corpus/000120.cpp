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

    std::vector<std::vector<int>> largeNestedVector(10, std::vector<int>(10));
    for (auto& vec : largeNestedVector) {
        for (int& val : vec) {
            val = rand() % 100; // Using rand with a fixed seed for determinism
        }
    }

    int largeResult = 0;
    for (const auto& vec : largeNestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                largeResult += val * sum;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result + largeResult << std::endl;
}