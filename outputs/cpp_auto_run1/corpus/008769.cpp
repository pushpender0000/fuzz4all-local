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
void processVector(const std::vector<T>& vec1, const std::vector<U>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cout << "Error: Vectors must be of the same size." << std::endl;
        return;
    }

    int result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if constexpr(IsSame<T, double>::value && IsSame<U, double>::value) {
            result += static_cast<int>(multiply(vec1[i], vec2[i]));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector1 = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<std::vector<double>> nestedVector2 = {{7.7, 8.8, 9.9}, {10.10, 11.11, 12.12}};

    processVector(nestedVector1[0], nestedVector2[1]);
}