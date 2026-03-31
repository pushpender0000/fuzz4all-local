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
void nestedTemplate() {
    std::vector<std::vector<U>> nestedVector;
    nestedVector.push_back({static_cast<U>(1), static_cast<U>(2), static_cast<U>(3)});
    nestedVector.push_back({static_cast<U>(4), static_cast<U>(5), static_cast<U>(6)});

    T result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<T, U>::value && IsSame<double, double>::value) {
            result += static_cast<int>(multiply(vec[1], add(static_cast<U>(5), static_cast<U>(7))));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    std::cout << result << std::endl;
}

int main() {
    nestedTemplate<int, double>();
}