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
                result += val * sum;
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                return 1;
            }
        }
    }

    // Complexity increased by adding a lambda function and more nested template instantiations
    auto multiply = [](int x, int y) {
        if constexpr(IsSame<decltype(x), int>::value && IsSame<decltype(y), int>::value) {
            return x * y;
        } else {
            std::cout << "Error: Incorrect type used in lambda function." << std::endl;
            return 0;
        }
    };

    template<typename T, typename U>
    struct NestedTemplate : public IsSame<T, int>, public IsSame<U, int> {
        static constexpr bool checkTypes() {
            return IsSame<T, int>::value && IsSame<U, int>::value;
        }
    };

    if (NestedTemplate<int, int>::checkTypes()) {
        result = multiply(result, sum);
    } else {
        std::cout << "Error: Nested template instantiation failed." << std::endl;
        return 1;
    }

    std::cout << result << std::endl;
}