#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) {
    return a * b;
}

template<typename T>
class Container {
public:
    Container(const std::vector<T>& values) : data_(values) {}

    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, void>>>
    auto sum() const {
        T sum = 0;
        for (const auto& item : data_) {
            if constexpr (std::is_arithmetic_v<T>) {
                sum += item;
            }
        }
        return sum;
    }

private:
    std::vector<T> data_;
};

template<typename T, typename U>
struct MultiplyWrapper {
    T value;
    U multiplier;

    constexpr auto multiplyValues() const {
        return multiply(value, multiplier);
    }
};

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    Container<int> container(vec);
    std::cout << container.sum() << "\n";

    MultiplyWrapper<int, double> wrapper{a, b};
    auto result = wrapper.multiplyValues();
    std::cout << "Result of multiplication: " << static_cast<int>(result) << "\n";

    return 0;
}