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
class NestedTemplate {
public:
    std::vector<std::vector<T>> data;

    NestedTemplate(const std::vector<std::vector<U>>& input) : data(input.size()) {
        for (size_t i = 0; i < input.size(); ++i) {
            if constexpr(IsSame<typename decltype(data)::value_type, T>::value) {
                data[i] = std::vector<T>(input[i].begin(), input[i].end());
            } else {
                throw std::invalid_argument("Incorrect type used in initialization.");
            }
        }
    }
};

int main() {
    constexpr int a = 5;
    constexpr int b = 7;
    auto sum = add(a, b);

    NestedTemplate<double, float> nestedVector({{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}});

    int result = 0;
    for (const auto& vec : nestedVector.data) {
        for (double val : vec) {
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