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
constexpr auto fibonacci(int n) -> std::vector<T> {
    if (n <= 0) return {};
    std::vector<T> fibSeq = {static_cast<T>(0), static_cast<T>(1)};
    for (int i = 2; i < n; ++i) {
        fibSeq.push_back(fibSeq[i - 1] + fibSeq[i - 2]);
    }
    return fibSeq;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        for (int val : vec) {
            if constexpr(IsSame<decltype(val), int>::value) {
                result += multiply(val, sum);
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    auto fibSeq = fibonacci<int>(10);
    for (const auto& val : fibSeq) {
        result += val * sum;
    }

    std::cout << result << std::endl;
}