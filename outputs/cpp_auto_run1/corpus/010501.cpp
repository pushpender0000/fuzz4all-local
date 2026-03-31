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
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);

    NestedTemplate<double> nestedVector;
    for (const auto& v : vec) {
        nestedVector.push_back({static_cast<double>(v), static_cast<double>(v + 1)});
    }

    int result = 0;
    for (const auto& vec2 : nestedVector) {
        if constexpr(IsSame<decltype(vec2[0]), double>::value) {
            result += std::accumulate(vec2.begin(), vec2.end(), 0, [](int sum, double val) -> int {
                return sum + static_cast<int>(multiply(val, add(1.0, -0.5)));
            });
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}