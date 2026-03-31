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
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T, std::size_t N>
constexpr auto sumArray(const T(&arr)[N]) -> T {
    T result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        result += arr[i];
    }
    return result;
}

template<typename T>
auto generateVector(T start, T end, std::vector<int>& vec) -> void {
    for (T i = start; i <= end; ++i) {
        if constexpr(std::is_arithmetic_v<T>) {
            vec.push_back(static_cast<int>(i));
        } else {
            std::cout << "Error: Type not arithmetic." << std::endl;
            return;
        }
    }
}

template<typename T, typename U>
auto nestedMultiplySum(const T& vec1, const U& vec2) -> void {
    if constexpr(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
        int result = 0;
        for (const auto& val1 : vec1) {
            for (const auto& val2 : vec2) {
                if constexpr(std::is_same_v<int, decltype(val1)> && std::is_same_v<int, decltype(val2>)) {
                    result += multiply(val1, sumArray({val2}));
                } else {
                    std::cout << "Error: Incorrect types used in calculation." << std::endl;
                    return;
                }
            }
        }
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Non-arithmetic vector type detected." << std::endl;
    }
}

int main() {
    constexpr int a[] = {1, 2, 3, 4, 5};
    constexpr std::size_t sizeA = sizeof(a) / sizeof(a[0]);
    auto sumArrayResult = sumArray<int, sizeA>(a);

    std::vector<std::vector<int>> nestedVector;
    generateVector(1, 3, nestedVector.emplace_back());
    generateVector(4, 6, nestedVector.emplace_back());

    nestedMultiplySum(nestedVector[0], nestedVector[1]);
}