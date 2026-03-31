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

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    processVector(nestedVector[0], nestedVector[1]);
}