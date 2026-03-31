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
constexpr auto sumArray(const T (&arr)[N]) -> T {
    T result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        result += arr[i];
    }
    return result;
}

int main() {
    constexpr int a = 5, b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    constexpr int arr[] = {1, 2, 3};
    auto arraySum = sumArray(arr);

    std::vector<std::vector<int>> nestedIntVector;
    nestedIntVector.push_back({10, 20, 30});
    nestedIntVector.push_back({40, 50, 60});

    int intResult = 0;
    for (const auto& vec : nestedIntVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                intResult += multiply(val, arraySum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result + intResult << std::endl;
}