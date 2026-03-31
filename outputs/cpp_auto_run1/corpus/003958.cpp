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
void processVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            std::cout << multiply(val, 2) << " ";
        } else if constexpr(IsSame<decltype(val), double>::value) {
            std::cout << add(val, val * 0.5) << " ";
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            exit(1);
        }
    }
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;

    std::vector<int> intVec = {1, 2, 3, 4, 5};
    std::vector<double> doubleVec = {1.1, 2.2, 3.3, 4.4, 5.5};

    processVector(intVec);
    processVector(doubleVec);

    return 0;
}