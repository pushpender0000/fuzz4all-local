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
    std::iota(vec.begin(), vec.end(), 1);

    NestedTemplate<double> nestedVector;
    for (const auto& v : vec) {
        if (v % 2 == 0) {
            nestedVector.push_back({static_cast<double>(v), static_cast<double>(v + 1)});
        } else {
            nestedVector.push_back({static_cast<double>(v)});
        }
    }

    int result = 0;
    for (const auto& vec : nestedVector) {
        if (!vec.empty()) {
            double sum = std::accumulate(vec.begin(), vec.end(), 0.0, [](double acc, double val) { return acc + val; });
            result += static_cast<int>(multiply(sum / vec.size(), sum / vec.size()));
        } else {
            std::cout << "Error: Empty vector encountered." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}