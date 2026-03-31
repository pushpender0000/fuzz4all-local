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
    std::vector<std::vector<T>> data;
    NestedTemplate(const std::vector<std::vector<U>>& other) : data(other.size()) {
        for (size_t i = 0; i < other.size(); ++i) {
            data[i].resize(other[i].size());
            for (size_t j = 0; j < other[i].size(); ++j) {
                data[i][j] = static_cast<T>(other[i][j]);
            }
        }
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    std::vector<std::vector<double>> nestedVector = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    NestedTemplate nt(nestedVector);

    int result = 0;
    for (const auto& vec : nt.data) {
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