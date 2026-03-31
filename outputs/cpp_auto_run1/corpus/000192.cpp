#include <iostream>
#include <vector>
#include <type_traits>
#include <cassert>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

template<typename T, typename F>
auto transformVector(const std::vector<T>& vec, F f) -> std::vector<decltype(f(vec[0]))> {
    std::vector<decltype(f(vec[0]))> result;
    for (const auto& val : vec) {
        result.push_back(f(val));
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    auto multiplySum = [sum](const int& val) { return val * sum; };
    std::vector<int> transformedVec = transformVector(nestedVector[0], multiplySum);

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

    assert(result == 63); // Ensure deterministic behavior
    std::cout << result << std::endl;
}