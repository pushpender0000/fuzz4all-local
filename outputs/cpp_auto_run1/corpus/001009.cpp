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
    void calculate(const std::vector<U>& vec) const {
        int result = 0;
        for (const auto& val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, add(T{}, T{})));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                std::exit(1);
            }
        }
        std::cout << result << std::endl;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    NestedTemplate<int, double> nt;
    nt.calculate(nestedVector[0]);
}