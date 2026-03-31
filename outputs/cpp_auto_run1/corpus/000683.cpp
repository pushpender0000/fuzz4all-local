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
void nestedMultiplyAdd(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cout << "Error: Vectors must be of the same size." << std::endl;
        return;
    }

    int result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if constexpr(IsSame<T, U>::value) {
            result += static_cast<int>(multiply(vec1[i], vec2[i]));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    constexpr T scalar = 3;
    result += add(scalar, scalar);
    std::cout << result << std::endl;
}

int main() {
    std::vector<int> vec1{1, 2, 3};
    std::vector<double> vec2{4.0, 5.0, 6.0};

    nestedMultiplyAdd(vec1, vec2);
}