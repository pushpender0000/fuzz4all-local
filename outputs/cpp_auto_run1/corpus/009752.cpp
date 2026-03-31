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
    constexpr int size = 3;
    NestedTemplate<double> nestedVector;
    for (int i = 0; i < size; ++i) {
        nestedVector.push_back({static_cast<double>(i + 1), static_cast<double>(i + 2)});
    }

    int result = 0;
    auto lambdaMultiplyAndAdd = [](auto val, auto sum) { return multiply(val, sum); };
    
    for (const auto& vec : nestedVector) {
        if constexpr(!vec.empty()) {
            double sumVec = std::accumulate(vec.begin(), vec.end(), 0.0);
            result += lambdaMultiplyAndAdd(sumVec, static_cast<double>(size));
        } else {
            std::cout << "Error: Empty vector in nested structure." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}