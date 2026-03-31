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
class NestedTemplate {
public:
    std::vector<std::vector<T>> nestedVector;
    NestedTemplate() {
        nestedVector.push_back({static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)});
        nestedVector.push_back({static_cast<T>(4), static_cast<T>(5), static_cast<T>(6)});
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double, float> nestedInstance;
    double result = 0.0;
    for (const auto& vec : nestedInstance.nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}