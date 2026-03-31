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
struct NestedTemplate {
    std::vector<T> data;
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double> nestedVector;
    nestedVector.data.push_back({1.1});
    nestedVector.data.push_back({2.2});
    nestedVector.data.push_back({3.3});
    nestedVector.data.push_back({4.4});
    nestedVector.data.push_back({5.5});
    nestedVector.data.push_back({6.6});

    int result = 0;
    for (const auto& vec : nestedVector.data) {
        if constexpr(IsSame<decltype(vec), double>::value) {
            result += static_cast<int>(multiply(vec, sum));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}