#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, size_t N>
constexpr auto sumArray(const T (&arr)[N]) -> T {
    T result = 0;
    for (size_t i = 0; i < N; ++i) {
        result += arr[i];
    }
    return result;
}

template<typename T>
constexpr auto multiply(T a, T b) -> T {
    return a * b;
}

int main() {
    constexpr int arr1[] = {1, 2, 3, 4, 5};
    constexpr int arr2[] = {6, 7, 8, 9, 10};
    auto sum1 = sumArray(arr1);
    auto sum2 = sumArray(arr2);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({11, 12, 13});
    nestedVector.push_back({14, 15, 16});

    int result = 0;
    auto lambdaMultiplySum = [&](const std::vector<int>& vec) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, sum1 + sum2);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
    };

    for (const auto& vec : nestedVector) {
        lambdaMultiplySum(vec);
    }

    std::cout << result << std::endl;
}