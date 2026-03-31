#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>

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

template<typename T>
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int size = 10;
    NestedTemplate<double> nestedVector;
    for (int i = 0; i < size; ++i) {
        std::vector<double> vec(size, static_cast<double>(i));
        nestedVector.push_back(vec);
    }

    int result = 0;
    auto sumLambda = [](const std::vector<double>& vec) -> double {
        return std::accumulate(vec.begin(), vec.end(), 0.0, add<double>);
    };

    for (const auto& vec : nestedVector) {
        result += static_cast<int>(sumLambda(vec));
    }

    std::cout << result << std::endl;
}