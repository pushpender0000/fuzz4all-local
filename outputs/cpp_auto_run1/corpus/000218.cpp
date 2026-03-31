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
auto multiplyNestedVectors(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    static_assert(IsSame<T, int>::value, "Type mismatch in nested vectors");
    static_assert(IsSame<U, int>::value, "Type mismatch in inner vector elements");

    T result = 0;
    for (const auto& vec : outerVec) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += val * add(1, 2); // Ensure we use a compile-time known value to avoid runtime checks
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return -1; // Signal error with a specific code for fuzzing purposes
            }
        }
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

    int result = multiplyNestedVectors(nestedVector, {7, 8, 9}); // Stress with a different type for inner vector to test robustness

    std::cout << result << std::endl;
}