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

template<typename T, typename U>
void processVectors(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    static_assert(!vec1.empty() && !vec2.empty(), "Vectors must not be empty");
    if constexpr (IsSame<int, T>::value && IsSame<int, U>::value) {
        int result = 0;
        for (const auto& val1 : vec1) {
            for (const auto& val2 : vec2) {
                result += multiply(val1, val2);
            }
        }
        std::cout << result << std::endl;
    } else {
        std::cout << "Error: Incorrect type used in calculation." << std::endl;
    }
}

int main() {
    constexpr int a[] = {1, 2, 3, 4, 5};
    constexpr std::size_t size = sizeof(a) / sizeof(a[0]);
    auto sumArrayResult = sumArray(a);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    processVectors(nestedVector[0], nestedVector[1]);
}