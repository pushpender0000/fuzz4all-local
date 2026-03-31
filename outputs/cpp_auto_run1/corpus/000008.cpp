#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
class Pair {
public:
    Pair(T first, U second) : first_(first), second_(second) {}

    template<typename V, typename W>
    auto add() const {
        return static_cast<V>(first_) + static_cast<W>(second_);
    }

private:
    T first_;
    U second_;
};

template<typename T, typename U>
constexpr auto multiply(T a, U b) {
    return a * b;
}

int main() {
    constexpr int x = 5;
    volatile double y = 3.14;

    auto lambda = [](auto x) {
        std::vector<decltype(x)> vec = {static_cast<decltype(x)>(1), static_cast<decltype(x)>(2), static_cast<decltype(x)>(3), static_cast<decltype(x)>(4), static_cast<decltype(x)>(5)};
        Pair pair(static_cast<int>(x), vec[0]);
        std::cout << pair.add<double, int>() << "\n";
        return x * x;
    };

    auto result = multiply(x, static_cast<int>(y));
    std::cout << "Result of multiplication: " << result << "\n";

    return lambda(result);
}