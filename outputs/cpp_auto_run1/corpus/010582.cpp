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
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int size = 10;
    constexpr double initial_value = 2.5;

    NestedTemplate<double> nestedVector;
    for (int i = 0; i < size; ++i) {
        std::vector<double> innerVec(size, initial_value);
        nestedVector.push_back(innerVec);
    }

    int result = 0;
    auto calculateSum = [](const std::vector<double>& vec) -> int {
        int sum = 0;
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                sum += static_cast<int>(multiply(val, add(1.0, -1.0)));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
        return sum;
    };

    for (const auto& vec : nestedVector) {
        result += calculateSum(vec);
    }

    std::cout << result << std::endl;
}