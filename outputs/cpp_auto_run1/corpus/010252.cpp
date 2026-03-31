#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
constexpr auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T>
class NestedTemplate : public std::vector<std::vector<T>> {};

constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

template<typename T, typename U>
void print_product(T a, U b) {
    auto product = multiply(a, b);
    std::cout << static_cast<int>(product) << std::endl;
}

int main() {
    constexpr int n = 10;
    consteval auto fib = [](auto n) {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    };

    NestedTemplate<int> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += val * fibonacci(n);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    std::cout << result << std::endl;
}