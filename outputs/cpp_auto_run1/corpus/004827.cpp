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
    std::vector<T> vec;
    void push_back(const T& val) {
        if constexpr (std::is_arithmetic_v<T>) {
            vec.push_back(val);
        } else {
            throw std::invalid_argument("Invalid type for container");
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
    nestedContainer.push_back(3.3);

    double result = 0;
    for (const auto& val : nestedContainer.vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += multiply(val, sum);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << static_cast<int>(result) << std::endl;
}