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
    std::vector<std::vector<T>> vec2d;
    constexpr int size = 5;
    for (int i = 0; i < size; ++i) {
        std::vector<U> innerVec(size, static_cast<U>(i + 1));
        vec2d.push_back(innerVec);
    }

    T result = 0;
    for (const auto& row : vec2d) {
        for (auto val : row) {
            if constexpr(IsSame<decltype(val), U>::value) {
                result += static_cast<T>(multiply(val, add(static_cast<U>(1), static_cast<U>(1))));
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