#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

template<typename T, typename F>
auto transformVector(const std::vector<T>& vec, F func) -> std::vector<std::invoke_result_t<F, T>> {
    std::vector<std::invoke_result_t<F, T>> result;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value || IsSame<decltype(val), float>::value) {
            result.push_back(func(val));
        } else {
            std::cout << "Error: Incorrect type used in transformation." << std::endl;
            exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr float b = 7.0f;
    auto sum = add(a, b);

    std::vector<std::vector<float>> nestedVector;
    nestedVector.push_back({1.0f, 2.0f, 3.0f});
    nestedVector.push_back({4.0f, 5.0f, 6.0f});

    auto multiplyBySum = [sum](auto val) { return val * sum; };
    auto transformedVector = transformVector(nestedVector[1], multiplyBySum);

    int result = 0;
    for (const auto& val : transformedVector) {
        if constexpr(IsSame<decltype(val), float>::value) {
            result += static_cast<int>(val);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}