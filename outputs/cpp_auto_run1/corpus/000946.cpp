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
    std::vector<std::vector<T>> nestedVector;
    nestedVector.push_back({static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)});
    nestedVector.push_back({static_cast<T>(4), static_cast<T>(5), static_cast<T>(6)});

    T result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), T>::value) {
                result += static_cast<int>(multiply(val, add(static_cast<T>(1), static_cast<T>(2))));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return;
            }
        }
    }

    std::cout << result << std::endl;
}

int main() {
    nestedTemplateInstantiation<double, int>();
}