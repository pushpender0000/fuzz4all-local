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
void complexOperation(const std::vector<std::vector<T>>& vec1, const std::vector<U>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cout << "Error: Vectors are of different sizes." << std::endl;
        return;
    }

    int result = 0;
    for (const auto& row : vec1) {
        if constexpr(IsSame<T, double>::value && IsSame<U, double>::value) {
            for (auto val : row) {
                result += static_cast<int>(multiply(val, add(static_cast<double>(row.size()), 0)));
            }
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return;
        }
    }

    for (const auto& val : vec2) {
        result += static_cast<int>(multiply(val, add(static_cast<U>(vec2.size()), 0)));
    }

    std::cout << result << std::endl;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    std::vector<int> vec2 = {7, 8, 9};

    complexOperation(nestedVector, vec2);
}