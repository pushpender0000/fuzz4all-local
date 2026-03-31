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

template<typename T, std::size_t N>
struct ArrayWrapper {
    T arr[N];
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    nestedVector.push_back({1.1, 2.2, 3.3});
    nestedVector.push_back({4.4, 5.5, 6.6});

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

    constexpr int x = 3;
    constexpr int y = 4;
    auto sub = add(x, y);

    ArrayWrapper<int, 3> arr1 = {{10, 20, 30}};
    ArrayWrapper<double, 3> arr2 = {{5.0, 6.0, 7.0}};

    auto lambdaAdd = [](auto a, auto b) { return add(a, b); };
    result += static_cast<int>(lambdaAdd(arr1.arr[0], arr2.arr[0]));

    std::cout << result << std::endl;
}