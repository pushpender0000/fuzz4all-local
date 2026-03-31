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

template<typename T>
class Container {
public:
    std::vector<T> data;
    constexpr void push_back(const T& val) {
        if (val > 0) {
            data.push_back(val);
        } else {
            throw std::invalid_argument("Value must be positive");
        }
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Container<double> nestedContainer;
    nestedContainer.push_back(1.1);
    nestedContainer.push_back(2.2);
    nestedContainer.push_back(-3.3); // This should trigger an error

    double result = 0;
    for (const auto& val : nestedContainer.data) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += multiply(val, sum);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}