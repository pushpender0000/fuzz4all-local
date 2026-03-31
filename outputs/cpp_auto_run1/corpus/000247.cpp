#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, int N>
constexpr auto multiply_elements(const std::vector<T>& vec) -> T {
    T result = 1;
    for (int i = 0; i < N; ++i) {
        if constexpr(IsSame<decltype(vec[i]), T>::value) {
            result *= vec[i];
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = multiply_elements<int, 2>(std::vector<int>{a, b});

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = 0;
    for (const auto& vec : nestedVector) {
        if constexpr(IsSame<decltype(vec[0]), int>::value) {
            result += multiply_elements<int, vec.size()>(vec);
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }

    std::cout << result << std::endl;
}