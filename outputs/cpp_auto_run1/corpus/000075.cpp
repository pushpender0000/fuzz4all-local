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

    std::vector<std::vector<std::vector<int>>> tripleNestedVector;
    tripleNestedVector.push_back({{7, 8}, {9, 10}});
    tripleNestedVector.push_back({{11, 12}, {13, 14}});

    int tripleResult = 0;
    for (const auto& middleVec : tripleNestedVector) {
        if constexpr(IsSame<decltype(middleVec[0][0]), int>::value) {
            for (const auto& innerVec : middleVec) {
                for (int val : innerVec) {
                    tripleResult += val * result;
                }
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << tripleResult << std::endl;
}