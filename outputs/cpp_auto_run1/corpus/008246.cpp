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
    T sum = 0;
    for (const auto& val : vec1) {
        if constexpr(IsSame<T, double>::value && IsSame<U, int>::value) {
            sum += static_cast<T>(multiply(val, *vec2.data()));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }
    std::cout << sum << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr double b = 7.0;
    auto sum = add(a, static_cast<decltype(sum)>(b));

    std::vector<double> vec1 = {1.1, 2.2, 3.3};
    std::vector<int> vec2 = {4, 5, 6};

    processVector(vec1, vec2);
}