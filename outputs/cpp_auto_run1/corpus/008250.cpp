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
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), double>::value) {
            result += static_cast<int>(multiply(val, N));
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            return 1;
        }
    }
    return result;
}

template<typename T>
constexpr auto generateVector(std::size_t size) -> std::vector<T> {
    std::vector<T> vec(size);
    for (auto& val : vec) {
        val = static_cast<T>(rand() % 100 + 1);
    }
    return vec;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector;
    for (int i = 0; i < 3; ++i) {
        nestedVector.push_back(generateVector<double>(rand() % 10 + 1));
    }

    int result = sumVector<double, 2>(nestedVector[0]);

    std::cout << result << std::endl;
}