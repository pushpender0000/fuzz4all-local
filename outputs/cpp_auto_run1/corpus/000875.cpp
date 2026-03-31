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
    std::vector<std::vector<T>> data;

    NestedTemplate(const std::vector<std::vector<T>>& vec) : data(vec) {}

    auto sumElements() const -> int {
        int result = 0;
        for (const auto& row : data) {
            for (const auto& val : row) {
                if constexpr(IsSame<decltype(val), T>::value && IsSame<T, U>::value) {
                    result += static_cast<int>(multiply(val, add(static_cast<T>(1), static_cast<T>(2))));
                } else {
                    std::cout << "Error: Incorrect type used in calculation." << std::endl;
                    return 1;
                }
            }
        }
        return result;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    NestedTemplate<double, double> nt(nestedVector);

    int result = nt.sumElements();

    std::cout << result << std::endl;
}