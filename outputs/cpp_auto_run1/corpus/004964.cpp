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

template<typename T, typename U>
void processVectors(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cout << "Error: Vectors must be of the same size." << std::endl;
        return;
    }

    T sum = 0;
    for (const auto& val : vec1) {
        if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
            sum += multiply(val, static_cast<T>(sumArray(&vec2[0])));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    std::cout << sum << std::endl;
}

int main() {
    constexpr int a = 5, b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<std::vector<int>> nestedVector2 = {{10, 20, 30}, {40, 50, 60}};

    processVectors(nestedVector1[0], nestedVector2[0]);
}