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
void print_sum_of_squares(const std::vector<T>& vec) {
    int result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, val));
        } else if constexpr(IsSame<decltype(val), int>::value) {
            result += add(val, val);
        } else {
            std::cout << "Error: Unsupported type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<double> doubleVec = {1.1, 2.2, 3.3};
    print_sum_of_squares(doubleVec);

    std::vector<int> intVec = {4, 5, 6};
    print_sum_of_squares(intVec);
}