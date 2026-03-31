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
    void push_back(const T& val) {
        if constexpr(std::is_arithmetic_v<T>) {
            data.push_back(val);
        } else {
            std::cout << "Error: Non-arithmetic type used." << std::endl;
        }
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    Container<double> doubleContainer;
    doubleContainer.push_back(1.1);
    doubleContainer.push_back(2.2);
    doubleContainer.push_back(3.3);

    int result = 0;
    for (const auto& val : doubleContainer.data) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}