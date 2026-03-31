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
        if constexpr(!vec.empty() && !innerVec.empty()) {
            int result = 0;
            for (const auto& val : vec) {
                if constexpr(IsSame<decltype(val), T>::value && IsSame<decltype(val), U>::value) {
                    result += static_cast<int>(multiply(val, add(val, val)));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return;
                }
            }
            std::cout << result << std::endl;
        } else {
            std::cout << "Error: Vector is empty." << std::endl;
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> innerVec = {7, 8, 9};

    nestedLoop(nestedVector, innerVec);
}