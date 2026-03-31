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

template<typename T, typename U>
void nestedLoop(const std::vector<std::vector<T>>& outerVec, const std::vector<U>& innerVec) {
    for (const auto& vec : outerVec) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
                std::cout << static_cast<int>(multiply(add(val, 1), add(val, 2))) << std::endl;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                exit(1);
            }
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> innerVec = {1, 2, 3};

    nestedLoop(nestedVector, innerVec);
}