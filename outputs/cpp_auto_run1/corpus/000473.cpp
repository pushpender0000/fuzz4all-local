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
    std::vector<U> nestedVector;

    auto sumElements() const {
        T result = 0;
        for (const auto& vec : nestedVector) {
            if constexpr(IsSame<decltype(vec), double>::value) {
                result += static_cast<T>(multiply(vec, add(static_cast<double>(1.5), static_cast<double>(2.5))));
            } else {
                std::cout << "Error: Incorrect type used in calculation." << std::endl;
                throw 1;
            }
        }
        return result;
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

    NestedTemplate<int, double> nt;
    nt.nestedVector = {1.1, 2.2, 3.3};

    try {
        auto result = nt.sumElements();
        std::cout << result << std::endl;
    } catch (int e) {
        return e;
    }
}