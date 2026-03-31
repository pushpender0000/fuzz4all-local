#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, typename... Args>
constexpr auto sum(Args... args) -> T {
    return (args + ...);
}

template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto totalSum = sum<int>(a, b);

    std::vector<std::vector<int>> nestedVector(2, std::vector<int>(3));
    nestedVector[0] = {1, 2, 3};
    nestedVector[1] = {4, 5, 6};

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, totalSum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}