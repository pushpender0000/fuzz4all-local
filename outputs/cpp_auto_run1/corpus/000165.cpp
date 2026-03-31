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

    // Mutation to increase complexity: adding more nested loops and template instantiations
    std::vector<std::vector<std::vector<int>>> tripleNestedVector;
    tripleNestedVector.push_back(nestedVector);
    tripleNestedVector.push_back(nestedVector);

    int tripleResult = 0;
    for (const auto& vec1 : tripleNestedVector) {
        for (const auto& vec2 : vec1) {
            for (int val : vec2) {
                if constexpr(IsSame<decltype(val), int>::value) {
                    tripleResult += val * sum;
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
    }

    // Mutation to use lambdas and consteval
    auto multiply = [](int x, int y) {
        constexpr int multiplier = 2;
        consteval int calc() {
            return x * y * multiplier;
        }
        return calc();
    };

    std::cout << "Triple Nested Result: " << tripleResult << ", Multiply Result: " << multiply(sum, sum) << std::endl;
}