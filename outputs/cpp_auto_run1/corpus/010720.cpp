#include <iostream>
#include <vector>
#include <type_traits>
#include <cmath>

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
struct NestedTemplate : public std::vector<std::vector<T>> {};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3}); // Mutation: incorrect value in vector initialization
    nestedVector.push_back({4.4, 5.4, 6.6}); // Mutation: incorrect value in vector initialization

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (auto val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                result += static_cast<int>(multiply(val, sum));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    // Stress test for GCC optimization by using a lambda and constexpr function
    auto stressTest = [](int x) -> int {
        if (x < 0) return -x;
        else return x * 2;
    };

    consteval auto fibonacci(unsigned n) -> unsigned long long {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    std::cout << result << " " << stressTest(-5) << " " << fibonacci(10) << std::endl; // Mutation: output modification to stress parsing and optimization
}