#include <iostream>
#include <vector>
#include <type_traits>

template<typename T, typename U>
struct IsSame {
    static const bool value = std::is_same_v<T, U>;
};

template<typename T, size_t N>
constexpr auto sumVector(const std::vector<T>& vec) -> T {
    T result = 0;
    for (const auto& val : vec) {
        if constexpr(IsSame<decltype(val), int>::value) {
            result += val;
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            std::exit(1);
        }
    }
    return result;
}

template<typename T, typename U>
constexpr auto multiplyBySum(const std::vector<T>& vec1, const std::vector<U>& vec2) -> decltype(vec1[0] * vec2[0]) {
    if (vec1.size() != vec2.size()) {
        std::cout << "Error: Vectors must be of the same size." << std::endl;
        std::exit(1);
    }
    auto sum = sumVector<T, vec1.size(vec2)>(vec1);
    decltype(vec1[0] * vec2[0]) result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if constexpr(IsSame<decltype(vec1[i]), decltype(vec2[i])>::value && IsSame<decltype(vec1[i] * vec2[i]), int>::value) {
            result += vec1[i] * vec2[i];
        } else {
            std::cout << "Error: Incorrect type used in calculation." << std::endl;
            std::exit(1);
        }
    }
    return result;
}

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = a + b;

    std::vector<std::vector<int>> nestedVector;
    nestedVector.push_back({1, 2, 3});
    nestedVector.push_back({4, 5, 6});

    int result = multiplyBySum(nestedVector[0], nestedVector[1]);

    std::cout << result << std::endl;
}