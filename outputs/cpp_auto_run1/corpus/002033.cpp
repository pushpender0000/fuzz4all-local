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

int main() {
    constexpr int a[] = {1, 2, 3, 4, 5};
    constexpr std::size_t size = sizeof(a) / sizeof(a[0]);
    auto sumArrayResult = sumArray(a);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<int, decltype(val)>::value) {
                result += multiply(val, sumArrayResult);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}