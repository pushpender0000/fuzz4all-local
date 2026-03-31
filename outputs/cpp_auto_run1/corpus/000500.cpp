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
struct NestedTemplate {
    T value;
    std::vector<U> vec;

    auto calculate() const {
        if constexpr (IsSame<T, int>::value) {
            int result = 0;
            for (const auto& val : vec) {
                result += multiply(val, this->value);
            }
            return result;
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            throw std::invalid_argument("Incorrect type");
        }
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.0, 2.0, 3.0});
    nestedVector.push_back({4.0, 5.0, 6.0});

    NestedTemplate<int, double> data{sum, {1.0, 2.0, 3.0}};
    std::cout << data.calculate() << std::endl;
}