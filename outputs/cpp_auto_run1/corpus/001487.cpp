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

template<typename T>
constexpr auto computeSum(const std::vector<T>& vec) -> T {
    T sum = 0;
    for (const auto& val : vec) {
        sum += static_cast<T>(val);
    }
    return sum;
}

int main() {
    constexpr int a = 5, b = 7;
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    
    auto sumVec = [](const std::vector<double>& vec) -> double {
        return computeSum(vec);
    };

    std::vector<int> intVector;
    for (auto& d : nestedVector[0]) {
        if constexpr(IsSame<decltype(d), double>::value) {
            intVector.push_back(static_cast<int>(multiply(d, sumVec(nestedVector[1])));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    int result = 0;
    for (int val : intVector) {
        result += val;
    }

    std::cout << result << std::endl;
}