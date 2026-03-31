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

    constexpr NestedTemplate() : data({{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}}) {}

    auto calculate(const T& scalar) const -> int {
        int result = 0;
        for (const auto& vec : data) {
            for (auto val : vec) {
                if constexpr(IsSame<decltype(val), T>::value) {
                    result += static_cast<int>(multiply(val, add(scalar, scalar)));
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
    NestedTemplate<double, double> nt;
    auto scalar = add(3.0, -2.0);
    std::cout << nt.calculate(scalar) << std::endl;
}