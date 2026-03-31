#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) {
    return a * b;
}

template<typename T, typename U>
class Pair {
public:
    Pair(T first, U second) : first_(first), second_(second) {}

    template<typename V, typename W>
    auto add() const {
        if constexpr (std::is_arithmetic_v<V> && std::is_arithmetic_v<W>) {
            return static_cast<V>(first_) + static_cast<W>(second_);
        } else {
            throw std::invalid_argument("Both types must be arithmetic.");
        }
    }

private:
    T first_;
    U second_;
};

int main() {
    constexpr int a = 5;
    volatile double b = 3.14;

    auto lambda = [](auto x) {
        return x * x;
    };

    std::vector<int> vec = {1, 2, 3, 4, 5};
    Pair<int, double> pair(a, b);

    try {
        auto result = pair.add<double, double>();
        std::cout << "Sum of first and second: " << result << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }

    auto squared = lambda(pair.add<double, double>());
    std::cout << "Squared sum: " << squared << "\n";

    return static_cast<int>(squared);
}