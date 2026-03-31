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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, add(1.0, -2.0)));
        } else if constexpr(IsSame<decltype(val), int>::value) {
            result += multiply(val, add(1, -2));
        } else {
            std::cout << "Error: Unsupported type in vector elements." << std::endl;
            exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int size = 5;
    std::vector<double> vecDouble(size, -3.0);
    std::vector<int> vecInt(size, -3);

    auto sumDoubles = sumVector(vecDouble);
    auto sumIntegers = sumVector(vecInt);

    std::cout << add(sumDoubles, sumIntegers) << std::endl;
}