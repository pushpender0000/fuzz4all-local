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
constexpr auto fibonacci(int n) -> std::enable_if_t<(n > 0), T> {
    if (n == 1) return T{0};
    if (n == 2) return T{1};
    T a = T{0}, b = T{1}, c;
    for (int i = 2; i < n; ++i) {
        c = add(a, b);
        a = b;
        b = c;
    }
    return b;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    constexpr int a = 5, b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector(10, std::vector<double>(10, 2.0));
    for (auto& vec : nestedVector) {
        for (auto& val : vec) {
            if constexpr(IsSame<decltype(val), double>::value) {
                val = multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

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

    std::cout << result << std::endl;
}