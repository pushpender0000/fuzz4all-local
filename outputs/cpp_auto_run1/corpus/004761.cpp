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
void nestedTemplateInstantiation() {
    std::vector<std::vector<U>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    T result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<T>(multiply(val, add(static_cast<U>(1), static_cast<U>(2))));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
            }
        }
    }
    std::cout << result << std::endl;
}

template<typename T, typename U>
void complexCalculation() {
    std::vector<T> vec1 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
    std::vector<U> vec2 = {1.1, 2.2, 3.3};

    T sumVec1 = 0;
    for (auto val : vec1) {
        sumVec1 += val;
    }

    U sumVec2 = 0;
    for (auto val : vec2) {
        sumVec2 += val;
    }

    T finalResult = static_cast<T>(multiply(sumVec1, add(static_cast<T>(4), static_cast<T>(5))));
    std::cout << "Final Result: " << finalResult << std::endl;
}

int main() {
    nestedTemplateInstantiation<int, double>();
    complexCalculation<int, double>();
}